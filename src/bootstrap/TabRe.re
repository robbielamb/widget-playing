include Utils;

type tab('a) = {
  tabId: 'a,
  x: bool => ReasonReact.reactElement
};

module Content = {
  let component = ReasonReact.statelessComponent("Tab.Content");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        ~active: 'a,
        children: array(tab('a))
      ) => {
    ...component,
    render: (_self) => {
      let classes = ["tab-content", unwrapStr(i, className)] |> String.concat(" ");
      let newChildren = Array.map((pane) => pane.x(pane.tabId == active), children);
      ReasonReact.createDomElement(tag, ~props={"className": classes}, newChildren)
    }
  };
};

module PaneComponent = {
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

module Pane = {
  let create = (~tabId: 'a, ~tag: string="div", ~className: option(string)=?, children) => {
    tabId,
    x: (active: bool) => <PaneComponent tag active ?className> children </PaneComponent>
  };
};