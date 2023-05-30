/// <reference lib="dom" />

import puppeteer from "https://deno.land/x/puppeteer@16.2.0/mod.ts";

const browser = await puppeteer.launch({
  args: [
    "--no-sandbox",
    "--disable-dev-shm-usage",
  ],
});

const page = await browser.newPage();

await page.goto(`file://${Deno.cwd()}/index.html`);

const { width, height } = await page.evaluate(() => {
  const body = document.body;
  const html = document.documentElement;

  const contentWidth = Math.max(
    body.scrollWidth,
    body.offsetWidth,
    html.clientWidth,
    html.scrollWidth,
    html.offsetWidth,
  );
  const contentHeight = Math.max(
    body.scrollHeight,
    body.offsetHeight,
    html.clientHeight,
    html.scrollHeight,
    html.offsetHeight,
  );

  return { width: contentWidth, height: contentHeight };
});

await page.setViewport({ width, height });

await page.screenshot({ path: "report.png", type: "png" });

await browser.close();
