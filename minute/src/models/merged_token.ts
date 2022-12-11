import { Attribute } from "./attriute";
import { Token } from "./token";

export type MergedToken = {
  id: number;
  elmType: "merged";
  content: string;
  parent: Token | MergedToken;
  attributes?: Attribute[];
};
