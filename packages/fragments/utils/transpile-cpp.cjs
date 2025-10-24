const fs = require('fs');
const path = require('path');
const { spawnSync } = require('child_process');

function usage() {
  console.log('Usage: node transpile-cpp.cjs <inputDir> <outputDir>');
}

if (process.argv.length < 4) {
  usage();
  process.exit(1);
}

// Accept multiple pairs: node transpile-cpp.cjs in1 out1 in2 out2 ...
const rawArgs = process.argv.slice(2);
if (rawArgs.length % 2 !== 0) {
  console.error('Expected pairs of <inputDir> <outputDir>. Got odd number of args.');
  usage();
  process.exit(1);
}

const pairs = [];
for (let i = 0; i < rawArgs.length; i += 2) {
  pairs.push({
    inputDir: path.resolve(rawArgs[i]),
    outputDir: path.resolve(rawArgs[i + 1]),
  });
}
// Resolve typescript2cxx CLI relative to this script's location so it works
// regardless of the current working directory when invoked.
const scriptDir = __dirname; // .../packages/fragments/utils
const toolsDir = path.resolve(scriptDir, '..', 'tools'); // .../packages/fragments/tools

// Candidate locations (normal and nested clone variations)
const candidates = [
  path.join(toolsDir, 'typescript2cxx', 'src', 'cli.ts'),
  path.join(toolsDir, 'packages', 'fragments', 'tools', 'typescript2cxx', 'src', 'cli.ts'),
  path.join(scriptDir, '..', '..', 'tools', 'typescript2cxx', 'src', 'cli.ts'),
  path.join(toolsDir, '..', 'packages', 'fragments', 'tools', 'typescript2cxx', 'src', 'cli.ts'),
  path.join(toolsDir, '..', 'packages', 'fragments', 'packages', 'fragments', 'tools', 'typescript2cxx', 'src', 'cli.ts'),
];

let cliPath = null;
let cliCwd = null;
for (const c of candidates) {
  if (fs.existsSync(c)) {
    cliPath = c;
    cliCwd = path.dirname(path.dirname(c)); // .../typescript2cxx
    break;
  }
}
if (!cliPath) {
  console.error('Cannot find typescript2cxx CLI. Tried:', candidates.join('\n'));
  process.exit(2);
}

// helper functions (unchanged signatures where possible)

function walk(dir, cb) {
  const entries = fs.readdirSync(dir, { withFileTypes: true });
  for (const e of entries) {
    const p = path.join(dir, e.name);
    if (e.isDirectory()) walk(p, cb);
    else if (e.isFile() && p.endsWith('.ts')) cb(p);
  }
}

function ensureDir(dir) {
  if (!fs.existsSync(dir)) fs.mkdirSync(dir, { recursive: true });
}

// Insert index_generated.h after include guard (#ifndef/#define) or after #pragma once
function insertIndexInclude(filePath) {
  try {
    const content = fs.readFileSync(filePath, 'utf8');
    if (content.includes('index_generated.h')) return;
    const lines = content.split('\n');

    // Look for pattern: #ifndef SOMETHING_H\n#define SOMETHING_H
    for (let i = 0; i < Math.min(10, lines.length); i++) {
      const l = lines[i].trim();
      if (l.startsWith('#ifndef')) {
        // find next #define within a few lines
        for (let j = i + 1; j <= i + 3 && j < lines.length; j++) {
          if (lines[j].trim().startsWith('#define')) {
            lines.splice(j + 1, 0, '', '#include "index_generated.h"', '');
            fs.writeFileSync(filePath, lines.join('\n'), 'utf8');
            return;
          }
        }
      }
      if (l.startsWith('#pragma once')) {
        // insert after this line
        lines.splice(i + 1, 0, '', '#include "index_generated.h"', '');
        fs.writeFileSync(filePath, lines.join('\n'), 'utf8');
        return;
      }
    }

    // fallback: prepend include
    fs.writeFileSync(filePath, '#include "index_generated.h"\n' + content, 'utf8');
  } catch (err) {
    console.error('Failed to insert index_generated.h to', filePath, err.message);
  }
}

function runTranspile(tsFile, outSubdir, currentInputDir) {
  ensureDir(outSubdir);
  console.log('Transpiling', path.relative(currentInputDir, tsFile), '->', path.relative(process.cwd(), outSubdir));
  const denoArgs = [
    'run',
    '--allow-read',
    '--allow-write',
    '--allow-env',
    '--allow-run',
    cliPath,
    '-o',
    outSubdir,
    tsFile,
  ];
  const res = spawnSync('deno', denoArgs, { stdio: 'inherit', cwd: cliCwd });
  if (res.error) {
    console.error('Failed to run deno:', res.error.message);
    process.exit(3);
  }
  if (res.status !== 0) {
    console.error('typescript2cxx failed for', tsFile, 'exit', res.status);
    process.exit(res.status || 4);
  }

  // post-process generated files: add index_generated.h include to any .h/.cpp
  const generated = fs.existsSync(outSubdir) ? fs.readdirSync(outSubdir, { withFileTypes: true }) : [];
  for (const g of generated) {
    const gp = path.join(outSubdir, g.name);
    if (g.isFile() && (gp.endsWith('.h') || gp.endsWith('.hpp') || gp.endsWith('.cpp') || gp.endsWith('.cc'))) {
      insertIndexInclude(gp);
    }
    if (g.isDirectory()) {
      walk(gp, (p) => {
        if (p.endsWith('.h') || p.endsWith('.hpp') || p.endsWith('.cpp') || p.endsWith('.cc')) insertIndexInclude(p);
      });
    }
  }
}

// Process each pair sequentially
for (const pair of pairs) {
  const { inputDir: currentInputDir, outputDir: currentOutputDir } = pair;
  if (!fs.existsSync(currentInputDir) || !fs.statSync(currentInputDir).isDirectory()) {
    console.warn('Input directory not found or is not a directory, skipping:', currentInputDir);
    continue;
  }
  // iterate all .ts and transpile individually for this pair
  walk(currentInputDir, (tsFile) => {
    const rel = path.relative(currentInputDir, tsFile);
    const outSubdir = path.join(currentOutputDir, path.dirname(rel));
    runTranspile(tsFile, outSubdir, currentInputDir);
  });
  console.log('All files transpiled to', currentOutputDir);
}
