import SimpleMVVM from "./index.js";
window.a = new SimpleMVVM({
  el: "#app",
  data: {
    name: "lingchen",
    age: 100,
    person: {
      name: "ger",
    },
  },
});
setTimeout(() => {
  a.name = "qqq";
}, 2000);
