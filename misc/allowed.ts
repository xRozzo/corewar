import $ from "https://deno.land/x/dax@0.30.1/mod.ts";

type Metadata = { green: number; dim: number; red: number };

const binary = Deno.args[0] ?? "invalid_bin";

const allowedSymbols = [
  "open",
  "read",
  "write",
  "fopen",
  "fread",
  "fwrite",
  "getline",
  "lseek",
  "fseek",
  "close",
  "fclose",
  "malloc",
  "realloc",
  "free",
  "exit",
];

await $`test -f ${binary}`;

const { stdout } = await $`nm ${binary}`.stdout("piped");

const { red: errors } = stdout.trim().split("\n").reduce<
  Metadata
>(
  (acc, line) => {
    if (line.indexOf(" U ") > 0) {
      const [, symbol] = line.split(" U ");
      const allowed = allowedSymbols.includes(
        symbol.indexOf("@") > 0 ? symbol.split("@")[0] : symbol,
      );
      const hidden = symbol.startsWith("_");
      const color = allowed ? "green" : hidden ? "dim" : "red";
      console.log(
        `::${color !== "red" ? "notice" : "error"}::Symbol ${symbol} found.`,
      );
      acc[color] = (acc[color] || 0) + 1;
    }
    return acc;
  },
  { dim: 0, green: 0, red: 0 },
);

if (errors > 0) {
  Deno.exit(1);
}

console.log(`::notice::Success, all symbols are allowed.`);
