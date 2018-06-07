/** Identity function */
let i = x => x;

let unwrapStr = (f, maybeStr) =>
  switch (maybeStr) {
  | Some(v) => f(v)
  | None => ""
  };
