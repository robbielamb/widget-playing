include Utils;

let component = ReasonReact.statelessComponent("Button");

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger
    | Link;
  let toString = (color) =>
    switch color {
    | Primary => "primary"
    | Secondary => "secondary"
    | Success => "success"
    | Info => "info"
    | Warning => "warning"
    | Danger => "danger"
    | Link => "link"
    };
};

module Size = {
  type t =
    | SM
    | LG;
  let toString = (size) =>
    switch size {
    | SM => "sm"
    | LG => "lg"
    };
};

let mapBool = (b) =>
  switch b {
  | None => Js.Nullable.null
  | Some(t) => Js.Nullable.return(Js.Boolean.to_js_boolean(t))
  };

let make =
    (
      ~tag: string="button",
      ~active: bool=false,
      ~block: bool=false,
      ~color: Color.t=Color.Secondary,
      ~disabled: bool=false,
      ~getRef: option([ | `String(string) | `Element(ReasonReact.reactElement)])=?,
      ~outline: bool=false,
      ~size: option(Size.t)=?,
      ~onClick: option((ReactEventRe.Mouse.t => unit))=?,
      ~ariaHaspopup: option(bool)=?,
      ~ariaExpanded: option(bool)=?,
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children
    ) => {
  ...component,
  render: (_self) => {
    let btnColor = "btn" ++ ((outline ? "-outline" : "") ++ ("-" ++ Color.toString(color)));
    let btnSize =
      switch size {
      | None => ""
      | Some(size) => "btn-" ++ Size.toString(size)
      };
    let classes =
      [
        "btn",
        btnColor,
        btnSize,
        block ? "btn-block" : "",
        active ? "active" : "",
        disabled ? "disabled" : "",
        unwrapStr(i, className)
      ]
      |> String.concat(" ");
    ReasonReact.createDomElement(
      tag,
      ~props={
        "className": classes,
        "onClick": Js.Nullable.from_opt(onClick),
        "aria-haspopup": mapBool(ariaHaspopup),
        "aria-expanded": mapBool(ariaExpanded)
      },
      children
    )
  }
};

/* TODO: Make this guy work */
module DropDown = {};

module Group = {
  module Size = {
    type t =
      | SM
      | LG;
    let toString = (size) =>
      "btn-group"
      ++ (
        switch size {
        | SM => "sm"
        | LG => "lg"
        }
      );
    let unwrap = Utils.unwrapStr(toString);
  };
  let component = ReasonReact.statelessComponent("Button.Group");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        ~role: string="group",
        ~size: option(Size.t)=?,
        ~vertical: bool=false,
        children
      ) => {
    ...component,
    render: (_self) => {
      let classes =
        [Size.unwrap(size), vertical ? "btn-group-vertical" : "btn-group", unwrapStr(i, className)]
        |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes, "role": role}, children)
    }
  };
};

module Toolbar = {
  let component = ReasonReact.statelessComponent("Button.Toolbar");
  let make = (~tag: string="div", ~className: option(string)=?, ~role: string="toolbar", children) => {
    ...component,
    render: (_self) => {
      let classes = ["btn-toolbar", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes, "role": role}, children)
    }
  };
};
