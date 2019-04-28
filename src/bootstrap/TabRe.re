include Utils;

type tab('a) = {
  tabId: 'a,
  x: bool => ReasonReact.reactElement,
};

module Content = {
  [@react.component]
  let make = (~className: option(string)=?, ~active: 'a, ~children: array(tab('a))) => {
    let className = ["tab-content", unwrapStr(i, className)] |> String.concat(" ");
    let newChildren = children->(Belt.Array.map(pane => pane.x(pane.tabId == active)));
    <div className> newChildren->React.array </div>;
  };
};

module PaneComponent = {
  let component = ReasonReact.statelessComponent("Tab.Pane");
  [@react.component]
  let make = (~active: bool=false, ~className: option(string)=?, ~children) => {
    let className = ["tab-pane", active ? "active" : "", unwrapStr(i, className)] |> String.concat(" ");
    <div className> children </div>;
  };
};

module Pane = {
  let create = (~tabId: 'a, ~key, ~className: option(string)=?, children) => {
    tabId,
    x: (active: bool) => <PaneComponent active key ?className> children </PaneComponent>,
  };
};