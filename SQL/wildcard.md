SQL提供了四种匹配模式：

1. % 表示任意0个或多个字符。如下语句：`Select * FROM user Where name LIKE '%三%';` 将会把name为“张三”，“三脚猫”，“唐三藏”等等有“三”的全找出来。%三：表示左匹配。三%：表示右匹配。

%三%：表示模糊查询。

2. \_ 表示任意单个字符。语句：`Select * FROM user Where name LIKE '_三_';`只找出“唐三藏”。这样name为三个字且中间一个字是“三”的; `Select * FROM user Where name LIKE '三__';` 只找出“三脚猫”这样name为三个字且第一个字是“三”的;

3. [ ] 表示括号内所列字符中的一个（类似与正则表达式）。语句：`Select * FROM user Where name LIKE '[张李王]三';` 将找出“张三”、“李三”、“王三”（而不是“张李王三”）; 如 [ ] 内有一系列字符（01234、abcde之类的）则可略写为“0-4”、“a-e“。`Select * FROM user Where name LIKE '老[1-9]';`将找出“老1”、“老2”、……、“老9”; 如要找“-”字符请将其放在首位：'张三\[-1-9]';

4. [^ ] 表示不在括号所列之内的单个字符。语句：`Select * FROM user Where name LIKE '[^张李王]三';`将找出不姓“张”、“李”、“王”的“赵三”、“孙三”等;`Select * FROM user Where name LIKE '老[^1-4]';`将排除“老1”到“老4”寻找“老5”、“老6”、……、“老9”。

5. * 表示查找的是所有信息,例如`select * from tbl_user`

最后是重点！由于通配符的缘故，导致我们查询特殊字符“%”、“\_”、“[”、“';”的语句无法正常实现，而把特殊字符用“[ ]”括起便可正常查询。据此我们写出以下函数： function sqlencode(str) str=replace(str,"';","';';") str=replace(str,"\[","\[[]") ';此句一定要在最先 str=replace(str,"\_","\[\_]") str=replace(str,"%","\[%]") sqlencode=str end function 在查询前将待查字符串先经该函数处理即可，并且在网页上连接数据库用到这类的查询语句时侯要注意：如Select * FROM user Where name LIKE '老\[^1-4]';上面《'》老\[^1-4]《'》是要有单引号的，别忘了，我经常忘！
