include Utils;

[@react.component]
let make = (~fluid: bool=false, ~className: option(string)=?, ~children) => {
  let className = ["jumbotron", fluid ? "jumbotron-fluid" : "", unwrapStr(i, className)] |> String.concat(" ");
  <div className> children </div>;
};

/* cssModule::(cssModule: option (Js.t {..}))=? */