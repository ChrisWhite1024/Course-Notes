# 变量
- JS 变量使用 let 或 var 声明
```
var myVariable;
let myVariable; // 块作用域局部变量
const myVariable; // 块作用域只读变量
```
- 标识符必须以字母、下划线或美元符号开头，后续可以是数字
- 变量对大小写敏感
```javascript
let myVariable = 'Chris'; //可以先定义后赋值也可以写在同一行
```
- 变量有不同的数据类型
```javascript
myVariable = 'Chris' // String（单引号双引号均可）
myVariable = 10 // Number
myVariable = true // Boolean
myVariable = [1, 'Chris', 'White'] // Array
myVariable = document.querySelector('h1'); //Object
``` 
- 声明但未赋值的变量，值为 undefined
- 访问未声明的变量会抛出引用错误
```

```

# 运算符
```javascript
let myVariable = 3;
myVariable === 4; // 等于运算符 
myVariable !== 4; // 不等于运算符
myVariable = "Hello" + "World" //加法运算符可拼接字符串
```
- === 和 == 不同，后者会进行类型转换
# 条件语句
- 与 C 语音相似
# 函数
```javascript
function multiply(num1, num2) {
  let result = num1 * num2;
  return result;
}
```
# 事件
- 可以使用元素提供的方法绑定事件名称和回调函数
```js
document.querySelector('html').addEventListener('click', function () {
alert("Hello");
}); //匿名函数 也可以写成箭头函数 () =>
```