let tokens = ["TokenNone",
/* "0x01 "*/ "TokenComma",
/* "0x02 "*/ "TokenAssign", "TokenAddAssign", "TokenSubtractAssign", "TokenMultiplyAssign", "TokenDivideAssign", "TokenModulusAssign",
/* "0x08 "*/ "TokenShiftLeftAssign", "TokenShiftRightAssign", "TokenArithmeticAndAssign", "TokenArithmeticOrAssign", "TokenArithmeticExorAssign",
/* "0x0d "*/ "TokenQuestionMark", "TokenColon",
/* "0x0f "*/ "TokenLogicalOr",
/* "0x10 "*/ "TokenLogicalAnd",
/* "0x11 "*/ "TokenArithmeticOr",
 /* "0x12 "*/ "TokenArithmeticExor",
 /* "0x13 "*/ "TokenAmpersand",
 /* "0x14 "*/ "TokenEqual", "TokenNotEqual",
 /* "0x16 "*/ "TokenLessThan", "TokenGreaterThan", "TokenLessEqual", "TokenGreaterEqual",
 /* "0x1a "*/ "TokenShiftLeft", "TokenShiftRight",
 /* "0x1c "*/ "TokenPlus", "TokenMinus",
 /* "0x1e "*/ "TokenAsterisk", "TokenSlash", "TokenModulus",
 /* "0x21 "*/ "TokenIncrement", "TokenDecrement", "TokenUnaryNot", "TokenUnaryExor", "TokenSizeof", "TokenCast",
 /* "0x27 "*/ "TokenLeftSquareBracket", "TokenRightSquareBracket", "TokenDot", "TokenArrow",
 /* "0x2b "*/ "TokenOpenBracket", "TokenCloseBracket",
 /* "0x2d "*/ "TokenIdentifier", "TokenIntegerConstant", "TokenFPConstant", "TokenStringConstant", "TokenCharacterConstant",
 /* "0x32 "*/ "TokenSemicolon", "TokenEllipsis",
 /* "0x34 "*/ "TokenLeftBrace", "TokenRightBrace",
 /* "0x36 "*/ "TokenIntType", "TokenCharType", "TokenFloatType", "TokenDoubleType", "TokenVoidType", "TokenEnumType",
 /* "0x3c "*/ "TokenLongType", "TokenSignedType", "TokenShortType", "TokenStaticType", "TokenAutoType", "TokenRegisterType", "TokenExternType", "TokenStructType", "TokenUnionType", "TokenUnsignedType", "TokenTypedef",
 /* "0x46 "*/ "TokenContinue", "TokenDo", "TokenElse", "TokenFor", "TokenGoto", "TokenIf", "TokenWhile", "TokenBreak", "TokenSwitch", "TokenCase", "TokenDefault", "TokenReturn",
 /* "0x52 "*/ "TokenHashDefine", "TokenHashInclude", "TokenHashIf", "TokenHashIfdef", "TokenHashIfndef", "TokenHashElse", "TokenHashEndif",
 /* "0x59 "*/ "TokenNew", "TokenDelete",
 /* "0x5b "*/ "TokenOpenMacroBracket",
 /* "0x5c "*/ "TokenEOF", "TokenEndOfLine", "TokenEndOfFunction"]

 let c = 'printf("e")'

 let out = `Token: 2d
 Token: 2b
 Token: 30
 Token: 2c
 Token: 5e
 Token: 5d
 Tokens: 2d 00 f4 d7 2e 01 2b 07 30 08 e4 99 2e 01 2c 0b 5e 0c 5d 00
 Got token=2d inc=1 pos=0
 ExpressionParse():
 Got token=2d inc=1 pos=0
 Got token=2b inc=0 pos=7
 Got token=2b inc=1 pos=7
 Expression stack [0x126c004,0x126bff4]: value=0:int[0x126bff4,0x126bfd8]
 ExpressionParse():
 Got token=30 inc=1 pos=8
 Expression stack [0x126c054,0x126c044]: value="e":string[0x126c044,0x126c028]
 Got token=2c inc=1 pos=11
 ExpressionStackCollapse(0):
 Expression stack [0x126c054,0x126c044]: value="e":string[0x126c044,0x126c028]
 ExpressionStackCollapse() finished
 Expression stack [0x126c054,0x126c044]: value="e":string[0x126c044,0x126c028]
 ExpressionParse() done
 
 Expression stack [0x126c044,0x126c044]: value="e":string[0x126c044,0x126c028]
 Got token=2c inc=1 pos=11
 e`
