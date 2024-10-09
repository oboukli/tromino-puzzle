
var createLitroMod = (() => {
  var _scriptName = typeof document != 'undefined' ? document.currentScript?.src : undefined;
  
  return (
function(moduleArg = {}) {
  var moduleRtn;

var g=moduleArg,h,k,l=new Promise((a,b)=>{h=a;k=b}),m=Object.assign({},g),n="",p;"undefined"!=typeof document&&document.currentScript&&(n=document.currentScript.src);_scriptName&&(n=_scriptName);n.startsWith("blob:")?n="":n=n.substr(0,n.replace(/[?#].*/,"").lastIndexOf("/")+1);p=a=>fetch(a,{credentials:"same-origin"}).then(b=>b.ok?b.arrayBuffer():Promise.reject(Error(b.status+" : "+b.url)));var q=console.error.bind(console);Object.assign(g,m);m=null;var r,v=!1,w,x=[],y=[],z=[],A=0,B=null,C=null;
function D(a){a="Aborted("+a+")";q(a);v=!0;a=new WebAssembly.RuntimeError(a+". Build with -sASSERTIONS for more info.");k(a);throw a;}var E=a=>a.startsWith("data:application/octet-stream;base64,"),F;function G(a){return p(a).then(b=>new Uint8Array(b),()=>{throw"both async and sync fetching of the wasm failed";})}function H(a,b,d){return G(a).then(c=>WebAssembly.instantiate(c,b)).then(d,c=>{q(`failed to asynchronously prepare wasm: ${c}`);D(c)})}
function I(a,b){var d=F;return"function"!=typeof WebAssembly.instantiateStreaming||E(d)||"function"!=typeof fetch?H(d,a,b):fetch(d,{credentials:"same-origin"}).then(c=>WebAssembly.instantiateStreaming(c,a).then(b,function(e){q(`wasm streaming compile failed: ${e}`);q("falling back to ArrayBuffer instantiation");return H(d,a,b)}))}function J(a){this.name="ExitStatus";this.message=`Program terminated with exit(${a})`;this.status=a}
var K=!0,L={},M=a=>{if(!(a instanceof J||"unwind"==a))throw a;},N=0,O=a=>{w=a;K||0<N||(v=!0);throw new J(a);},P=a=>{if(!v)try{if(a(),!(K||0<N))try{w=a=w,O(a)}catch(b){M(b)}}catch(b){M(b)}},Q=[],R,S=a=>{var b=Q[a];b||(a>=Q.length&&(Q.length=a+1),Q[a]=b=R.get(a));return b},T,U=[],W={c:()=>{D("")},b:()=>{K=!1;N=0},d:(a,b)=>{L[a]&&(clearTimeout(L[a].id),delete L[a]);if(!b)return 0;var d=setTimeout(()=>{delete L[a];P(()=>V(a,performance.now()))},b);L[a]={id:d,l:b};return 0},a:O},X=function(){var a={a:W};
A++;F??=E("litro-wasm.wasm")?"litro-wasm.wasm":n+"litro-wasm.wasm";I(a,function(b){X=b.instance.exports;r=X.e;b=r.buffer;new Int8Array(b);new Int16Array(b);new Uint8Array(b);new Uint16Array(b);new Int32Array(b);new Uint32Array(b);new Float32Array(b);new Float64Array(b);R=X.i;y.unshift(X.f);A--;0==A&&(null!==B&&(clearInterval(B),B=null),C&&(b=C,C=null,b()))}).catch(k);return{}}();g._solve=(a,b,d,c)=>(g._solve=X.g)(a,b,d,c);var V=(a,b)=>(V=X.h)(a,b);
g.addFunction=(a,b)=>{if(!T){T=new WeakMap;var d=R.length;if(T)for(var c=0;c<0+d;c++){var e=S(c);e&&T.set(e,c)}}if(d=T.get(a)||0)return d;if(U.length)d=U.pop();else{try{R.grow(1)}catch(t){if(!(t instanceof RangeError))throw t;throw"Unable to grow wasm table. Set ALLOW_TABLE_GROWTH.";}d=R.length-1}try{c=d,R.set(c,a),Q[c]=R.get(c)}catch(t){if(!(t instanceof TypeError))throw t;if("function"==typeof WebAssembly.Function){c=WebAssembly.Function;e={i:"i32",j:"i64",f:"f32",d:"f64",e:"externref",p:"i32"};
for(var u={parameters:[],results:"v"==b[0]?[]:[e[b[0]]]},f=1;f<b.length;++f)u.parameters.push(e[b[f]]);b=new c(u,a)}else{c=[1];e=b.slice(0,1);b=b.slice(1);u={i:127,p:127,j:126,f:125,d:124,e:111};c.push(96);f=b.length;128>f?c.push(f):c.push(f%128|128,f>>7);for(f=0;f<b.length;++f)c.push(u[b[f]]);"v"==e?c.push(0):c.push(1,u[e]);b=[0,97,115,109,1,0,0,0,1];e=c.length;128>e?b.push(e):b.push(e%128|128,e>>7);b.push(...c);b.push(2,7,1,1,101,1,102,0,0,7,5,1,1,102,0,0);b=new WebAssembly.Module(new Uint8Array(b));
b=(new WebAssembly.Instance(b,{e:{f:a}})).exports.f}c=d;R.set(c,b);Q[c]=R.get(c)}T.set(a,d);return d};g.removeFunction=a=>{T.delete(S(a));R.set(a,null);Q[a]=R.get(a);U.push(a)};var Y;C=function aa(){Y||Z();Y||(C=aa)};function Z(){if(!(0<A)){for(;0<x.length;)x.shift()(g);if(!(0<A||Y||(Y=!0,g.calledRun=!0,v))){for(;0<y.length;)y.shift()(g);for(h(g);0<z.length;)z.shift()(g)}}}Z();moduleRtn=l;


  return moduleRtn;
}
);
})();
if (typeof exports === 'object' && typeof module === 'object')
  module.exports = createLitroMod;
else if (typeof define === 'function' && define['amd'])
  define([], () => createLitroMod);
