import { generate } from "./generator";
import { parse } from "./parser";

const convertToHTMLString = (markdown: string) => {
  const mdArray = markdown.split(/\r\n|\r|\n/);
  const asts = mdArray.map((md) => parse(md));
  const htmlString = generate(asts);
  return htmlString;
};

console.log(convertToHTMLString("normal"));

// convertToHTMLString("* list1\n* list2")[0].forEach((obj) => {
//   console.log(obj);
// });
