import Notifier from "./notifier.js";
import Compiler from "./compiler.js";
import Observer from "./observer.js";

export default class SimpleMVVM {
  constructor(options = {}) {
    this.$options = options;

    this.notifier = new Notifier("data-change");

    this.observer = new Observer(this);
    this.$data = this.observer.reactive(this.$options.data);
    this.observer.observe(this.$data);

    this.compiler = new Compiler(this);
    this.compiler.compile(this.$options.el);
  }

  notify(value) {
    this.notifier.publish(value);
  }

  subscribe(callback) {
    this.notifier.subscribe(callback);
  }

  getValue(key) {
    const keys = key.split(".");
    let val = this;
    keys.forEach((key) => {
      val = val[key];
    });
    return val;
  }

  getValueAndParent(key) {
    const keys = key.split(".");
    let val = this;
    let parentVal = this;
    let lastKey;
    keys.forEach((key) => {
      parentVal = val;
      val = val[key];
      lastKey = key;
    });

    return [val, parentVal, lastKey];
  }
}
