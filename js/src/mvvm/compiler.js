import { getPlainValue } from "./utils.js";

export default class Compiler {
  constructor(vm) {
    this.vm = vm;
  }

  /**
   * 编译传入的元素
   * @param {string} el 需要编译的元素选择器
   */
  compile(el) {
    // 使用fragment，编译完成后一次修改数据，减少对dom的操作
    const element = document.querySelector(el);
    const fragment = document.createDocumentFragment();
    Array.from(element.childNodes).forEach((ele) => {
      fragment.appendChild(ele);
    });
    this.replace(fragment);
    element.appendChild(fragment);
  }

  /**
   * 编译模板
   * @param {HTMLElement} element 编译的元素
   */
  replace(element) {
    const reg = /\{\{(.*)\}\}/i;
    [].forEach.call(element.childNodes, (node) => {
      switch (node.nodeType) {
        case 1:
          this._compileAttr(node);
          break;
        case 3:
          this._compileText(node);
          break;
      }
      if (node.childNodes.length) {
        this.replace(node);
      }
    });
  }

  /**
   * 编译元素中的文本内容
   * @param {HTMLElement} node 被编译的元素
   */
  _compileText(node) {
    const reg = /\{\{(.*)\}\}/i;
    const { vm } = this;
    const template = node.textContent;

    if (reg.test(template)) {
      const key = RegExp.$1;
      const replaceText = () => {
        const val = vm.getValue(key);
        node.textContent = template.replace(reg, getPlainValue(val));
      };
      replaceText();

      vm.subscribe(replaceText);
    }
  }

  /**
   * 编译元素的属性
   * @param {HTMLElement} node 被编译的元素
   */
  _compileAttr(node) {
    const attrs = node.attributes;
    const { vm } = this;
    Array.from(attrs).forEach((attr) => {
      const { name, value } = attr;
      if (name.startsWith("v-")) {
        // 数据变动后修改属性值
        vm.subscribe(() => {
          const val = vm.getValue(value);
          attr.value = getPlainValue(val);
        });

        // 根据key拿到对应的值和它的父对象，方便后续在属性值变动时修改数据
        const [val, parent, realKey] = vm.getValueAndParent(value);
        node.value = getPlainValue(val);

        node.addEventListener("input", () => {
          parent[realKey] = getPlainValue(node.value);
        });
      }
    });
  }
}
