import { generate } from "./generator";
import { analize } from "./lexer";
import { parse } from "./parser";

const convertToHTMLString = (markdown: string) => {
  const mdArray = analize(markdown);
  const asts = mdArray.map((md) => parse(md));
  const htmlString = generate(asts);
  return htmlString;
};

console.log(convertToHTMLString("normal text\n\n- **bold text**\n- list2"));

// convertToHTMLString("* list1\n* list2")[0].forEach((obj) => {
//   console.log(obj);
// });
