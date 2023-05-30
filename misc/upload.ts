import { config } from "https://deno.land/x/dotenv@v3.2.2/mod.ts";
import data from "../data.json" assert { type: "json" };

config({
  allowEmptyValues: false,
  export: true,
  path: "../.env"
});

const WEBHOOK_URL = Deno.args[0] ?? Deno.env.get("WEBHOOK_URL");

const content = `- ${data.id}
 - passed: "${
  ((data.passed / (data.passed + data.errored + data.failed + data.skipped)) *
    100).toFixed(2)
}%"
 - tests:
 ${
  data.test_suites.reduce<string[]>((acc, item) => [
    ...acc,
    `\n    - name: ${item.name}
     - passed: "${
      ((item.passed /
        (item.passed + item.errored + item.failed + item.skipped)) *
        100).toFixed(2)
    }%"
     - tests:
         ${
      item.tests.reduce<string[]>(
        (
          acc,
          test,
        ) => [
          ...acc,
          `    - ${test.name}: "${test.status} (${test.assertions} assertions)"`,
        ],
        [],
      ).join("\n        ")
    }`,
  ], []).join("\n")
}
 `;

await Deno.writeFile("./report.yaml", new TextEncoder().encode(content));

const form = new FormData();

form.append(
  "payload_json",
  JSON.stringify({
    content: `\`\`\`md\n# Criterion test report\n\`\`\``,
  }),
);

form.set(
  "file",
  new Blob([await Deno.readFile(`./report.yaml`)], {
    type: "application/x-yaml",
  }),
  "report.yaml",
);

form.set(
  "file2",
  new Blob([await Deno.readFile(`./report.png`)], { type: "image/png" }),
  "report.png",
);

const req = await fetch(WEBHOOK_URL, {
  body: form,
  method: "POST",
});

if (!req.ok) {
  await fetch(WEBHOOK_URL, {
    method: "POST",
    body: JSON.stringify(
      `\`\`\`json\n${JSON.stringify(await req.json(), null, 2)}\n\`\`\``,
    ),
  });
}
