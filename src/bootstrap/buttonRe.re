include Utils;

let component = ReasonReact.statelessComponent "Button";

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger
    | Link;
  let toString color =>
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
  let toString size =>
    switch size {
    | SM => "sm"
    | LG => "lg"
    };
};

let mapBool b =>
  switch b {
  | None => Js.Undefined.empty
  | Some t => Js.Undefined.return (Js.Boolean.to_js_boolean t)
  };

let make
    tag::(tag: string)="button"
    active::(active: bool)=false
    block::(block: bool)=false
    color::(color: Color.t)=Color.Secondary
    disabled::(disabled: bool)=false
    getRef::(getRef: option [ | `String string | `Element ReasonReact.reactElement])=?
    outline::(outline: bool)=false
    size::(size: option Size.t)=?
    onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
    ariaHaspopup::(ariaHaspopup: option bool)=?
    ariaExpanded::(ariaExpanded: option bool)=?
    className::(className: option string)=?
    /* cssModule::(cssModule: option (Js.t {..}))=? */
    children => {
  ...component,
  render: fun self => {
    let click event _self =>
      disabled ?
        ReactEventRe.Mouse.preventDefault event :
        (
          switch onClick {
          | None => ()
          | Some cb => cb event
          }
        );
    let btnColor = "btn" ^ (outline ? "-outline" : "") ^ "-" ^ Color.toString color;
    let btnSize =
      switch size {
      | None => ""
      | Some size => "btn-" ^ Size.toString size
      };
    let classes =
      [
        "btn",
        btnColor,
        btnSize,
        block ? "btn-block" : "",
        active ? "active" : "",
        disabled ? "disabled" : "",
        unwrapStr i className
      ]
      |> String.concat " ";
    ReasonReact.createDomElement
      tag
      props::{
        "className": classes,
        "onClick": self.handle click,
        "aria-haspopup": mapBool ariaHaspopup,
        "aria-expanded": (mapBool ariaExpanded)
      }
      children
  }
};

/* TODO: Make this guy work */
module DropDown = {};

module Group = {
  module Size = {
    type t =
      | SM
      | LG;
    let toString size =>
      "btn-group"
      ^ (
        switch size {
        | SM => "sm"
        | LG => "lg"
        }
      );
    let unwrap = Utils.unwrapStr toString;
  };
  let component = ReasonReact.statelessComponent "Button.Group";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      role::(role: string)="group"
      size::(size: option Size.t)=?
      vertical::(vertical: bool)=false
      children => {
    ...component,
    render: fun _self => {
      let classes =
        [Size.unwrap size, vertical ? "btn-group-vertical" : "btn-group", unwrapStr i className]
        |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
    }
  };
};

module Toolbar = {
  let component = ReasonReact.statelessComponent "Button.Toolbar";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      role::(role: string)="toolbar"
      children => {
    ...component,
    render: fun _self => {
      let classes = ["btn-toolbar", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
    }
  };
};