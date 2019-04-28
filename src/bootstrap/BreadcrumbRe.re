include Utils;

[@react.component]
let make = (~className: option(string)=?, ~children) => {
  let className = ["breadcrumb", unwrapStr(i, className)] |> String.concat(" ");
  <ol className> children </ol>;
};

module Item = {
  [@react.component]
  let make = (~active: bool=false, ~className: option(string)=?, ~children) => {
    let className = ["breadcrumb-item", active ? "active" : "", unwrapStr(i, className)] |> String.concat(" ");
    <li className> children </li>;
  };
};

