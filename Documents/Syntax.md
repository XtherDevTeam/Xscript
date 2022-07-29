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

### UnnamedFunctionDefinition

Status: `Implmented`

Syntax: `UnnamedFunctionDefinition ::= "func" "("  [ { Expression "," } Expression ] ")" CodeBlock`

### Arguments

Status: `Implmented`

Syntax: `Arguments ::= TokenLeftParentheses [ Expression { ", " Expression } ] TokenRightParentheses`

### CrossPackageAccessExpression

Status: `Implmented`

Syntax:

```
CrossPackageAccessExpression ::= "@" "{" TokenString "}" TokenToSign MemberExpression
```

### NewExpression

Status: `Implmented`

Syntax:

```
NewExpression ::= "new" MemberExpression
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
NegativeExpression ::= TokenMinus ( MemberExpression | UnnamedFunctionDefinition | Primary )
                     | ( MemberExpression | UnnamedFunctionDefinition | Primary )
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

### InstanceOfExpression

Status: `Implemented`

Syntax:

```
InstanceOfExpression ::= AdditionExpression "instanceOf" Identifier
                       | AdditionExpression
```

### BinaryMoveExpression

Status: `Implmented`

Syntax:

```
BinaryMoveExpression ::= InstanceOfExpression ( TokenBinaryLeftMove | TokenBinaryRightMove ) BinaryMoveExpression
                       | InstanceOfExpression
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

### TryCatchStatement

Status: `Implmented`

Syntax:

```
TryCatchStatement ::= "try" CodeBlock "catch" "as" Identifier CodeBlock
```

### VariableStatement

Status: `Implmented`

Syntax:

```
VariableStatement ::= "var" Identifier
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
FunctionDefinition ::= "function" Identifier Arguments CodeBlock
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

### MemberDefineStatement

Status: `Implmented`

Syntax:

```
DefineStatement ::= "def" Identifier "in" Expression  
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
ClassDefinition ::= "class" Identifier "extends" Identifier LeftBrace { MethodDefinition } RightBrace
```

### ImportStatement

Status: `Implmented`

Syntax:

```
ImportStatement ::= "import" TokenString
```

### NativeClassDeclarationStatement

Status: `Implmented`

Syntax:

```
NativeClassDeclarationStatement ::= "native_class" Identifier "in" TokenString
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
                | NativeClassDeclarationStatement
```

### File

Status: `Implmented`

Syntax:

```
File ::= { FileStatement }
```