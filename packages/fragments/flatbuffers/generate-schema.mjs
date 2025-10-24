#!/usr/bin/env node
import { execSync } from "child_process";
import * as fs from "fs";
import * as path from "path";

const root = path.resolve(process.cwd()); // expected to be packages/fragments when run from package
const flatbuffersDir = path.resolve(root, "flatbuffers");
const targetFlatc = path.join(flatbuffersDir, "flatc");
const targetFlatcc = path.join(flatbuffersDir, "flatcc");
const fbsFile = path.join(flatbuffersDir, "index.fbs");

function findBinary(name, possiblePaths = []) {
  try {
    const which = execSync(`which ${name}`, { stdio: ["pipe", "pipe", "ignore"] }).toString().trim();
    if (which) return which;
  } catch (e) {
    // ignore
  }
  for (const p of possiblePaths) {
    if (fs.existsSync(p)) return p;
  }
  return null;
}

function run(cmd) {
  console.log(`> ${cmd}`);
  execSync(cmd, { stdio: "inherit" });
}

async function main() {
  if (!fs.existsSync(fbsFile)) {
    console.error(`Schema file not found: ${fbsFile}`);
    process.exit(1);
  }

  // ensure output dirs (relative to current package root `root`)
  // const ffiSchema = path.resolve(root, "../fragments/../ffi/Schema");
  const cppSchema = path.resolve(root, "../fragments/../cpp/Schema");
  const tsSchema = path.resolve(root, "src/Schema");
  // Normalize intended paths: when running from packages/fragments, desired targets are
  // packages/fragments/ffi/Schema, packages/fragments/cpp/Schema, packages/fragments/src/Schema
  // const fixedFfi = path.resolve(root, "ffi/Schema");
  const fixedCpp = path.resolve(root, "cpp/Schema");
  const fixedTs = path.resolve(root, "src/Schema");
  // fs.mkdirSync(fixedFfi, { recursive: true });
  fs.mkdirSync(fixedCpp, { recursive: true });
  fs.mkdirSync(fixedTs, { recursive: true });

  // Locate system flatc (FlatBuffers compiler). We will prefer the system
  // binary for detection and invocation to avoid using a stale copy bundled in
  // the repo. The script will still copy the binary into the flatbuffers
  // folder for reproducibility but won't switch the runtime binary to that
  // copied path.
  let systemFlatc = findBinary("flatc", ["/usr/local/bin/flatc", "/opt/homebrew/bin/flatc", "/usr/bin/flatc"]);
  // let flatcc = findBinary("flatcc", ["/usr/local/bin/flatcc", "/opt/homebrew/bin/flatcc", "/usr/bin/flatcc"]);
  let flatc = systemFlatc;

  // If missing, attempt to install via brew (first flatc, then flatcc)
  try {
    const brewPath = execSync("which brew", { stdio: ["pipe", "pipe", "ignore"] }).toString().trim();
    if (brewPath) {
      if (!systemFlatc) {
        console.log("flatc not found in PATH. Homebrew found, installing flatbuffers via brew...");
        run("brew install flatbuffers");
        systemFlatc = findBinary("flatc", ["/usr/local/bin/flatc", "/opt/homebrew/bin/flatc", "/usr/bin/flatc"]);
        flatc = systemFlatc;
      }
      // if (!flatcc) {
      //   console.log("flatcc not found in PATH. Homebrew found, installing flatcc via brew...");
      //   run("brew install flatcc");
      //   flatcc = findBinary("flatcc", ["/usr/local/bin/flatcc", "/opt/homebrew/bin/flatcc", "/usr/bin/flatcc"]);
      // }
    }
  } catch (e) {
    // no brew available, continue: we'll error out later if binaries are missing
  }

  // if (!flatc && !flatcc) {
  if (!systemFlatc) {
    console.error("flatc was not found. Please install flatbuffers (brew install flatbuffers), or place the binary at packages/fragments/flatbuffers/");
    process.exit(1);
  }

  // copy found binaries into the package flatbuffers folder for reproducibility
  if (systemFlatc) {
    try {
      const dest = targetFlatc;
      fs.copyFileSync(systemFlatc, dest);
      fs.chmodSync(dest, 0o755);
      // keep using system flatc for detection and invocation to avoid stale copies
      flatc = systemFlatc;
      console.log(`Copied flatc to ${dest}; using system flatc: ${flatc}`);
    } catch (e) {
      console.warn(`Could not copy flatc to ${targetFlatc}, will use system flatc`);
      flatc = systemFlatc;
    }
  }
  // if (flatcc) {
  //   try {
  //     const dest = targetFlatcc;
  //     fs.copyFileSync(flatcc, dest);
  //     fs.chmodSync(dest, 0o755);
  //     flatcc = dest;
  //     console.log(`Using flatcc: ${flatcc}`);
  //   } catch (e) {
  //     console.warn(`Could not copy flatcc to ${targetFlatcc}, will use system flatcc`);
  //   }
  // }

  // run generation
  const cwd = flatbuffersDir;
  try {
    // Run generation for each available generator.
    if (flatc) {
      // detect supported C++ standard by parsing `flatc --help`
      let cppStd = "--cpp-std=c++17";
      try {
        const help = execSync(`${flatc} --help`, { stdio: ["pipe", "pipe", "ignore"] }).toString();
        // prefer c++20 if explicitly listed, otherwise fall back to c++17 or c++11
        if (help.includes("c++20")) {
          cppStd = "--cpp-std=c++20";
          console.log("flatc help lists c++20; using --cpp-std=c++20");
        } else if (help.includes("c++17")) {
          cppStd = "--cpp-std=c++17";
          console.log("flatc help lists c++17; using --cpp-std=c++17");
        } else if (help.includes("c++11") || help.includes("c++0x")) {
          cppStd = "--cpp-std=c++11";
          console.log("flatc help lists c++11/c++0x; using --cpp-std=c++11");
        } else {
          console.log("flatc help did not list a supported C++ std; defaulting to c++17");
          cppStd = "--cpp-std=c++17";
        }
      } catch (err) {
        console.log("Could not parse flatc help; defaulting to --cpp-std=c++17");
        cppStd = "--cpp-std=c++17";
      }

      // generate C++ bindings with detected C++ standard
      //  --gen-onefile \
      run(`${flatc} --cpp \
  ${cppStd} \
  --gen-mutable \
  --gen-object-api \
  --gen-compare \
  --gen-name-strings \
  --cpp-include <memory> \
  --cpp-include <string> \
  -o ${fixedCpp} ${fbsFile}`);
      // generate TypeScript bindings (mutable)
      run(`${flatc} --gen-mutable -o ${fixedTs} --ts ${fbsFile}`);
    } else {
      console.log('flatc not available, skipping C++ and TypeScript generation that require flatc.');
    }

    // // flatcc generates C sources/headers
    // if (flatcc) {
    //   // -a generates accessors, builders and verifier headers
    //   // -o specifies output dir
    //   run(`${flatcc} -a -o ${fixedFfi} ${fbsFile}`);
    // } else {
    //   console.log('flatcc not available, skipping C generation.');
    // }
    console.log("Generation finished.");
  } catch (e) {
    console.error("flatc generation failed", e);
    process.exit(1);
  }
}

main().catch((e) => {
  console.error(e);
  process.exit(1);
});
