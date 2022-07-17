
var createLitroMod = (() => {
  var _scriptDir = typeof document !== 'undefined' && document.currentScript ? document.currentScript.src : undefined;
  
  return (
function(createLitroMod) {
  createLitroMod = createLitroMod || {};


null;var a;a||(a=typeof createLitroMod !== 'undefined' ? createLitroMod : {});var k,l;a.ready=new Promise(function(b,c){k=b;l=c});var m=Object.assign({},a),n="";"undefined"!=typeof document&&document.currentScript&&(n=document.currentScript.src);_scriptDir&&(n=_scriptDir);0!==n.indexOf("blob:")?n=n.substr(0,n.replace(/[?#].*/,"").lastIndexOf("/")+1):n="";var p=a.printErr||console.warn.bind(console);Object.assign(a,m);m=null;var q;a.wasmBinary&&(q=a.wasmBinary);var noExitRuntime=a.noExitRuntime||!0;
"object"!=typeof WebAssembly&&r("no native wasm support detected");var t,u=!1,w,x=[],y=[],z=[];function A(){var b=a.preRun.shift();x.unshift(b)}var B=0,C=null,D=null;function r(b){if(a.onAbort)a.onAbort(b);b="Aborted("+b+")";p(b);u=!0;b=new WebAssembly.RuntimeError(b+". Build with -sASSERTIONS for more info.");l(b);throw b;}function E(){return F.startsWith("data:application/octet-stream;base64,")}var F;F="litro-wasm.wasm";if(!E()){var G=F;F=a.locateFile?a.locateFile(G,n):n+G}
function H(){var b=F;try{if(b==F&&q)return new Uint8Array(q);throw"both async and sync fetching of the wasm failed";}catch(c){r(c)}}function I(){return q||"function"!=typeof fetch?Promise.resolve().then(function(){return H()}):fetch(F,{credentials:"same-origin"}).then(function(b){if(!b.ok)throw"failed to load wasm binary file at '"+F+"'";return b.arrayBuffer()}).catch(function(){return H()})}function J(b){for(;0<b.length;)b.shift()(a)}var K=[];
function L(b){var c=K[b];c||(b>=K.length&&(K.length=b+1),K[b]=c=w.get(b));return c}var M=void 0,N=[],O={};
(function(){function b(d){a.asm=d.exports;t=a.asm.a;d=t.buffer;a.HEAP8=new Int8Array(d);a.HEAP16=new Int16Array(d);a.HEAP32=new Int32Array(d);a.HEAPU8=new Uint8Array(d);a.HEAPU16=new Uint16Array(d);a.HEAPU32=new Uint32Array(d);a.HEAPF32=new Float32Array(d);a.HEAPF64=new Float64Array(d);w=a.asm.d;y.unshift(a.asm.b);B--;a.monitorRunDependencies&&a.monitorRunDependencies(B);0==B&&(null!==C&&(clearInterval(C),C=null),D&&(d=D,D=null,d()))}function c(d){b(d.instance)}function h(d){return I().then(function(f){return WebAssembly.instantiate(f,
e)}).then(function(f){return f}).then(d,function(f){p("failed to asynchronously prepare wasm: "+f);r(f)})}var e={a:O};B++;a.monitorRunDependencies&&a.monitorRunDependencies(B);if(a.instantiateWasm)try{return a.instantiateWasm(e,b)}catch(d){return p("Module.instantiateWasm callback failed with error: "+d),!1}(function(){return q||"function"!=typeof WebAssembly.instantiateStreaming||E()||"function"!=typeof fetch?h(c):fetch(F,{credentials:"same-origin"}).then(function(d){return WebAssembly.instantiateStreaming(d,
e).then(c,function(f){p("wasm streaming compile failed: "+f);p("falling back to ArrayBuffer instantiation");return h(c)})})})().catch(l);return{}})();a.___wasm_call_ctors=function(){return(a.___wasm_call_ctors=a.asm.b).apply(null,arguments)};a._solve=function(){return(a._solve=a.asm.c).apply(null,arguments)};
a.addFunction=function(b,c){if(!M){M=new WeakMap;var h=w.length;if(M)for(var e=0;e<0+h;e++){var d=L(e);d&&M.set(d,e)}}if(M.has(b))return M.get(b);if(N.length)h=N.pop();else{try{w.grow(1)}catch(v){if(!(v instanceof RangeError))throw v;throw"Unable to grow wasm table. Set ALLOW_TABLE_GROWTH.";}h=w.length-1}try{e=h,w.set(e,b),K[e]=w.get(e)}catch(v){if(!(v instanceof TypeError))throw v;if("function"==typeof WebAssembly.Function){e=WebAssembly.Function;d={i:"i32",j:"i64",f:"f32",d:"f64",p:"i32"};for(var f=
{parameters:[],results:"v"==c[0]?[]:[d[c[0]]]},g=1;g<c.length;++g)f.parameters.push(d[c[g]]);c=new e(f,b)}else{e=[1,96];d=c.slice(0,1);c=c.slice(1);f={i:127,p:127,j:126,f:125,d:124};g=c.length;128>g?e.push(g):e.push(g%128|128,g>>7);for(g=0;g<c.length;++g)e.push(f[c[g]]);"v"==d?e.push(0):e.push(1,f[d]);c=[0,97,115,109,1,0,0,0,1];d=e.length;128>d?c.push(d):c.push(d%128|128,d>>7);c.push.apply(c,e);c.push(2,7,1,1,101,1,102,0,0,7,5,1,1,102,0,0);c=new WebAssembly.Module(new Uint8Array(c));c=(new WebAssembly.Instance(c,
{e:{f:b}})).exports.f}e=h;w.set(e,c);K[e]=w.get(e)}M.set(b,h);return h};a.removeFunction=function(b){M.delete(L(b));N.push(b)};var P;D=function Q(){P||R();P||(D=Q)};
function R(){function b(){if(!P&&(P=!0,a.calledRun=!0,!u)){J(y);k(a);if(a.onRuntimeInitialized)a.onRuntimeInitialized();if(a.postRun)for("function"==typeof a.postRun&&(a.postRun=[a.postRun]);a.postRun.length;){var c=a.postRun.shift();z.unshift(c)}J(z)}}if(!(0<B)){if(a.preRun)for("function"==typeof a.preRun&&(a.preRun=[a.preRun]);a.preRun.length;)A();J(x);0<B||(a.setStatus?(a.setStatus("Running..."),setTimeout(function(){setTimeout(function(){a.setStatus("")},1);b()},1)):b())}}
if(a.preInit)for("function"==typeof a.preInit&&(a.preInit=[a.preInit]);0<a.preInit.length;)a.preInit.pop()();R();


  return createLitroMod.ready
}
);
})();
if (typeof exports === 'object' && typeof module === 'object')
  module.exports = createLitroMod;
else if (typeof define === 'function' && define['amd'])
  define([], function() { return createLitroMod; });
else if (typeof exports === 'object')
  exports["createLitroMod"] = createLitroMod;
