export default class Notify {
  constructor(event) {
    this.event = event;
    this.notifies = [];
  }
  /**
   * 订阅消息
   * @param {function} callback
   */
  subscribe(callback) {
    this.notifies.push(callback);
  }
  /**
   * 发送通知
   * @param {any} data 传给订阅者的数据
   */
  publish(data) {
    this.notifies.forEach((notify) => {
      notify(data);
    });
  }
}
