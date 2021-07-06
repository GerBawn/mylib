export function getPlainValue(value) {
  return typeof value === "object" ? JSON.stringify(value) : value;
}
