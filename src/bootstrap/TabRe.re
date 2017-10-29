include Utils;

module Content = {
  let component = ReasonReact.statelessComponent("Tab.Content");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: (_self) => {
      let classes = ["tab-content", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
  };
};

module Pane = {
  let component = ReasonReact.statelessComponent("Tab.Pane");
  let make = (~tag: string="div", ~active: bool=false, ~className: option(string)=?, children) => {
    ...component,
    render: (_self) => {
      let classes =
        ["tab-pane", active ? "active" : "", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
  };
};
