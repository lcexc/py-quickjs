import os
import qjs

code = '''import * as std from 'std';


((G)=>{
    const sys_path = std.getenv('PATH');
    console.log("run .....");
    G._r = 'result: '+ sys_path;
})(globalThis);

'''

code1 = '(()=>{return Date.now();})();'

mod_test = '''import * as m from '../lib/toolm.dll'

console.log("Hello World 你好");

console.log(m.echo("Hello , 哈哈"));

console.log(m.md5('123456'));'''

print("work dir:", os.getcwd())
print(qjs.eval_js(code))
print(qjs.eval_js(code1))

print(qjs.eval_js(mod_test))




