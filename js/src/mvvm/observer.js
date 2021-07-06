import { getPlainValue } from "./utils.js";
export default class Observer {
  constructor(vm) {
    this.vm = vm;
  }

  /**
   * 将传入的数据变成响应式
   * @param {any} data 数据
   * @returns {any}
   */
  reactive(data) {
    const res = {};
    const that = this;
    for (let key in data) {
      const value = data[key];
      Object.defineProperty(res, key, {
        enumerable: true,
        get() {
          return data[key];
        },
        set(newVal) {
          if (newVal === value) {
            return;
          }
          const text = getPlainValue(newVal);
          data[key] = text;
          that.vm.notify(text);
        },
      });
      if (typeof value === "object") {
        this.reactive(value);
      }
    }
    return res;
  }

  /**
   * 将传入的数据绑定到vm上
   * @param {any} data 需要观察的对象
   */
  observe(data) {
    const that = this;
    for (let key in data) {
      Object.defineProperty(that.vm, key, {
        enumerable: true,
        get() {
          return data[key];
        },
        set(newVal) {
          data[key] = newVal;
        },
      });
    }
  }
}
