import { Attribute } from "./attriute";

export type Token = {
  id: number;
  parent: Token;
  elmType: string;
  content: string;
  attributes?: Attribute[];
};
