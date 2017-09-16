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
    let btnColor = cn ("btn" ^ (outline ? "-outline" : "") ^ "-" ^ Color.toString color);
    let btnSize =
      switch size {
      | None => ocn ("n", false)
      | Some size => cn ("btn-" ^ Size.toString size)
      };
    let classes =
      classNameReduce
        className
        [
          cn "btn",
          btnColor,
          btnSize,
          ocn ("btn-block", block),
          ocn ("active", active),
          ocn ("disabled", disabled)
        ];
    ReasonReact.createDomElement
      tag props::{"className": classes, "onClick": self.handle click} children
  }
};

module DropDown = {};

module Group = {
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
  let component = ReasonReact.statelessComponent "Button.Group";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      role::(role: string)="group"
      size::(size: option Size.t)=?
      vertical::(vertical: bool)=false
      children => {
    let btnSize =
      switch size {
      | None => ocn ("n", false)
      | Some size => cn ("btn-group" ^ Size.toString size)
      };
    let classes =
      classNameReduce className [btnSize, cn (vertical ? "btn-group-vertical" : "btn-group")];
    ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
  };
};

module Toolbar = {
  let component = ReasonReact.statelessComponent "Button.Toolbar";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      role::(role: string)="toolbar"
      children => {
    let classes = classNameReduce className [cn "btn-toolbar"];
    ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
  };
};