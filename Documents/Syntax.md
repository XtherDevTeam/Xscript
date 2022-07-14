### XScript Syntax Document

### Primary

Status: `Implmented`

Syntax:

```
Primary ::= TokenInteger | TokenDecimal | TokenString
          | TokenLeftParentheses Expression TokenRightParentheses
```

### Identifier

Status: `Implmented`

Syntax: `Identifier ::= TokenIdentifier | CrossPackageAccessExpression`

### ListLiteral

Status: `Implmented`

Syntax: `ListLiteral ::= "[" [ { Expression "," } Expression ] "]"`

### Arguments

Status: `Implmented`

Syntax: `Arguments ::= TokenLeftParentheses [ Expression { ", " Expression } ] TokenRightParentheses`

### CrossPackageAccessExpression

Status: `Unimplmented`

Syntax:

```
CrossPackageAccessExpression ::= "@" "{" TokenString "}" TokenToSign MemberExpression
```

### IndexExpression

Status: `Implmented`

Syntax:

```
IndexExpression ::= IndexExpression TokenLeftBracket Expression TokenRightBracket
                  | Identifier TokenLeftbracket Expression TokenRightBracket
                  | Identifier
```

### FunctionCallingExpression

Status: `Implmented`

Syntax:

```
FunctionCallingExpression ::= IndexExpression Arguments
```

### MemberExpression

Status: `Implmented`

Syntax:

```
MemberExpression ::= MemberExpression TokenDot FunctionCallingExpression
                   | FunctionCallingExpression [ TokenDot FunctionCallingExpression ]
```

### NegativeExpression

Status: `Implmented`

Syntax:

```
NegativeExpression ::= TokenMinus ( MemberExpression | Primary )
                     | ( MemberExpression | Primary )
```

### IncrementExpression

Status: `Implmented`

Syntax:

```
IncrementExpression ::= TokenIncrementSign NegativeExpression
                      | NegativeExpression
```

### DecrementExpression

Status: `Implmented`

Syntax:

```
DecrementExpression ::= TokenDecrementSign NegativeExpression
                      | NegativeExpression
```

### MultiplicationExpression

Status: `Implmented`

Syntax:

```
MultiplicationExpression ::= ( IncrementExpression | DecrementExpression ) ( TokenAsterisk | TokenSlash | TokenReminderSign ) MultiplicationExpression
                           | ( IncrementExpression | DecrementExpression )
```

### AdditionExpression

Status: `Implmented`

Syntax:

```
MultiplicationExpression ::= MultiplicationExpression ( TokenPlus | TokenMinus ) AdditionExpression
                           | MultiplicationExpression
```

### BinaryMoveExpression

Status: `Implmented`

Syntax:

```
BinaryMoveExpression ::= AdditionExpression ( TokenBinaryLeftMove | TokenBinaryRightMove ) BinaryMoveExpression
                       | AdditionExpression
```

### ComparingExpression

Status: `Implmented`

Syntax:

```
ComparingExpression ::= BinaryMoveExpression ( TokenLessThanOrEqual | TokenMoreThanOrEqual | TokenLessThan | TokenMoreThan ) ComparingExpression
                      | BinaryMoveExpression
```

### EqualExpression

Status: `Implmented`

Syntax:

```
ComparingExpression ::= ComparingExpression ( TokenEqual | TokenNotEqual ) ComparingExpression
                      | ComparingExpression
```

### BinaryExpression

Status: `Implmented`

Syntax:

```
BinaryExpression ::= EqualExpression ( TokeBinaryXOR | TokenBinaryOr | TokenBinaryAnd ) BinaryExpression
                   | EqualExpression
```

### LogicExpression

Status: `Implmented`

Syntax:

```
LogicExpression ::= BinaryExpression ( TokenLogicAnd | TokenLogicOr ) LogicExpression
                  | BinaryExpression
```

### AssignmentExpression

Status: `Implmented`

Syntax:

```
AssignmentExpression ::= MemberExpression ( TokenAssignSign | TokenAdditionAssignment | TokenSubtractionAssignment | TokenMultiplationAssignment | TokenDivisionAssignment | RemainderAssignment ) LogicExpression
```

### Expression

Status: `Implmented`

Syntax:

```
Expression ::= LogicExpression
             | AssignmentExpression
```

### VariableStatementNodeGenerator

Status: `Implmented`

Syntax:

```
VariableStatementNodeGenerator ::= "var" Identifier
```

### VariableDefinitionStatement

Status: `Implmented`

Syntax:

```
VariableDefinitionStatement ::= "var" Identifier TokenEqual Expression
```

### WhileStatement

Status: `Implmented`

Syntax:

```
WhileStatement ::= "while" "(" Expression ")" CodeBlock
```

### ForStatement

Status: `Implmented`

Syntax:

```
ForStatement ::= "for" "(" Statement ";" Expression ";" Statement ")" CodeBlock
```

### IfStatement

Status: `Implmented`

Syntax:

```
IfStatement ::= "if" "(" Expression ")" CodeBlock
```

### IfElseStatement

Status: `Implmented`

Syntax:

```
IfElseStatement ::= "if" "(" Expression ")" CodeBlock "else" Statement
```

### BreakStatement

Status: `Implmented`

Syntax:

```
BreakStatement ::= "break"
```

### ContinueStatement

Status: `Implmented`

Syntax:

```
ContinueStatement ::= "continue"
```

### ReturnStatement

Status: `Implmented`

Syntax:

```
ReturnStatement ::= "return" Expression
```

### FunctionDefinition

Status: `Implmented`

Syntax:

```
FunctionDefinitionNodeGenerator ::= "function" Identifier Arguments CodeBlock
```

### MethodDescriptor

Status: `Implmented`

Syntax:

```
MethodDescriptor ::= "virtual" | "final" | "public" | "private"
```

### MethodDefinition

Status: `Implmented`

Syntax:

```
MethodDefinition ::= MethodDescriptor FunctionDefinition
```

### MemberDescriptor

Status: `Implmented`

Syntax:

```
MemberDescriptor ::= "public" | "private" 
```

### MemberDeclaration

Status: `Implmented`

Syntax:

```
MemberDeclaration ::= MemberDescriptor VariableDeclaration
```

### CodeBlock

Status: `Implmented`

Syntax:

```
CodeBlock ::= "{" { Statement ";" } "}"
```

### ClassDefinition

Status: `Implmented`

Syntax:

```
ClassDefinition ::= "class" Identifier "extends" LeftParentheses { Identifier } RightParentheses LeftBrace { MethodDefinition } RightBrace
```

### PackageStatement

Status: `Implmented`

Syntax:

```
PackageStatement ::= "package" TokenString
```

### ImportStatement

Status: `Implmented`

Syntax:

```
ImportStatement ::= "import" TokenString
```

### FileStatement

Status: `Implmented`

Syntax:

```
FileStatement ::= FunctionDefinition
                | VariableDefinition
                | VariableDeclaration
                | ImportStatement
                | PackageStatement
```

### File

Status: `Implmented`

Syntax:

```
File ::= { FileStatement }
```