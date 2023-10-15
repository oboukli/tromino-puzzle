
var createLitroMod = (() => {
  var _scriptDir = typeof document !== 'undefined' && document.currentScript ? document.currentScript.src : undefined;
  
  return (
function(moduleArg = {}) {

var d=moduleArg,h,k;d.ready=new Promise((b,a)=>{h=b;k=a});var l=Object.assign({},d),m="";"undefined"!=typeof document&&document.currentScript&&(m=document.currentScript.src);_scriptDir&&(m=_scriptDir);0!==m.indexOf("blob:")?m=m.substr(0,m.replace(/[?#].*/,"").lastIndexOf("/")+1):m="";var n=console.error.bind(console);Object.assign(d,l);l=null;"object"!=typeof WebAssembly&&p("no native wasm support detected");var q,r=!1,v=[],w=[],x=[],y=0,z=null,A=null;
function p(b){b="Aborted("+b+")";n(b);r=!0;b=new WebAssembly.RuntimeError(b+". Build with -sASSERTIONS for more info.");k(b);throw b;}var B=b=>b.startsWith("data:application/octet-stream;base64,"),C;C="litro-wasm.wasm";B(C)||(C=m+C);function D(){throw"both async and sync fetching of the wasm failed";}
function E(b){return"function"==typeof fetch?fetch(b,{credentials:"same-origin"}).then(a=>{if(!a.ok)throw"failed to load wasm binary file at '"+b+"'";return a.arrayBuffer()}).catch(()=>D()):Promise.resolve().then(()=>D())}function F(b,a,e){return E(b).then(c=>WebAssembly.instantiate(c,a)).then(c=>c).then(e,c=>{n(`failed to asynchronously prepare wasm: ${c}`);p(c)})}
function G(b,a){var e=C;return"function"!=typeof WebAssembly.instantiateStreaming||B(e)||"function"!=typeof fetch?F(e,b,a):fetch(e,{credentials:"same-origin"}).then(c=>WebAssembly.instantiateStreaming(c,b).then(a,function(f){n(`wasm streaming compile failed: ${f}`);n("falling back to ArrayBuffer instantiation");return F(e,b,a)}))}
var H=[],I,J=b=>{var a=H[b];a||(b>=H.length&&(H.length=b+1),H[b]=a=I.get(b));return a},K,L=[],M={},N=function(){var b={a:M};y++;G(b,function(a){N=a.instance.exports;q=N.a;a=q.buffer;d.HEAP8=new Int8Array(a);d.HEAP16=new Int16Array(a);d.HEAPU8=new Uint8Array(a);d.HEAPU16=new Uint16Array(a);d.HEAP32=new Int32Array(a);d.HEAPU32=new Uint32Array(a);d.HEAPF32=new Float32Array(a);d.HEAPF64=new Float64Array(a);I=N.d;w.unshift(N.b);y--;0==y&&(null!==z&&(clearInterval(z),z=null),A&&(a=A,A=null,a()))}).catch(k);
return{}}();d._solve=(b,a,e,c)=>(d._solve=N.c)(b,a,e,c);
d.addFunction=(b,a)=>{if(!K){K=new WeakMap;var e=I.length;if(K)for(var c=0;c<0+e;c++){var f=J(c);f&&K.set(f,c)}}if(e=K.get(b)||0)return e;if(L.length)e=L.pop();else{try{I.grow(1)}catch(t){if(!(t instanceof RangeError))throw t;throw"Unable to grow wasm table. Set ALLOW_TABLE_GROWTH.";}e=I.length-1}try{c=e,I.set(c,b),H[c]=I.get(c)}catch(t){if(!(t instanceof TypeError))throw t;if("function"==typeof WebAssembly.Function){c=WebAssembly.Function;f={i:"i32",j:"i64",f:"f32",d:"f64",e:"externref",p:"i32"};
for(var u={parameters:[],results:"v"==a[0]?[]:[f[a[0]]]},g=1;g<a.length;++g)u.parameters.push(f[a[g]]);a=new c(u,b)}else{c=[1];f=a.slice(0,1);a=a.slice(1);u={i:127,p:127,j:126,f:125,d:124,e:111};c.push(96);g=a.length;128>g?c.push(g):c.push(g%128|128,g>>7);for(g=0;g<a.length;++g)c.push(u[a[g]]);"v"==f?c.push(0):c.push(1,u[f]);a=[0,97,115,109,1,0,0,0,1];f=c.length;128>f?a.push(f):a.push(f%128|128,f>>7);a.push.apply(a,c);a.push(2,7,1,1,101,1,102,0,0,7,5,1,1,102,0,0);a=new WebAssembly.Module(new Uint8Array(a));
a=(new WebAssembly.Instance(a,{e:{f:b}})).exports.f}c=e;I.set(c,a);H[c]=I.get(c)}K.set(b,e);return e};d.removeFunction=b=>{K.delete(J(b));I.set(b,null);H[b]=I.get(b);L.push(b)};var O;A=function P(){O||Q();O||(A=P)};function Q(){if(!(0<y)){for(;0<v.length;)v.shift()(d);if(!(0<y||O||(O=!0,d.calledRun=!0,r))){for(;0<w.length;)w.shift()(d);for(h(d);0<x.length;)x.shift()(d)}}}Q();


  return moduleArg.ready
}

);
})();
if (typeof exports === 'object' && typeof module === 'object')
  module.exports = createLitroMod;
else if (typeof define === 'function' && define['amd'])
  define([], () => createLitroMod);
