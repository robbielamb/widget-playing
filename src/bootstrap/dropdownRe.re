include Utils;

module Color = ButtonRe.Color;

module Size = ButtonRe.Size;

type retainedProps = {isOpen: bool};

let component = ReasonReact.statelessComponentWithRetainedProps "Dropdown";

let make
    tag::(tag: string)="div"
    disabled::(disabled: bool)=false
    group::(group: bool)=false
    right::(right: bool)=false
    isOpen::(isOpen: bool)=false
    classname::(classname: option string)=?
    children => {
  ...component,
  retainedProps: isOpen,
  render:
    fun (_self: ReasonReact.self ReasonReact.stateless retainedProps ReasonReact.actionless) => {
    let classNames =
      ["dropdown", isOpen ? "show" : "", unwrapStr i classname] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classNames} children
  }
};

module Toggle = {
  let component = ReasonReact.statelessComponent "Dropdown.Toggle";
  let make
      tag::(tag: option string)=?
      caret::(caret: bool)=false
      disabled::(disabled: bool)=false
      right::(right: bool)=false
      isOpen::(isOpen: bool)=false
      split::(split: bool)=false
      color::(color: Color.t)=Color.Secondary
      nav::(nav: bool)=false
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      togggle::(toggle: option (unit => unit))=?
      classname::(classname: option string)=?
      children => {
    ...component,
    retainedProps: isOpen,
    render: fun _self => {
      let classNames =
        [
          caret || split ? "dropdown-toggle" : "",
          split ? "dropdown-toggle-split" : "",
          isOpen ? "active" : "",
          unwrapStr i classname
        ]
        |> String.concat " ";
      let tag =
        switch (tag, nav) {
        | (None, true) => "a"
        | (None, false) => "button"
        | (Some t, _) => t
        };
      switch tag {
      | "button" =>
        ReasonReact.element (ButtonRe.make ::color className::classNames ::?onClick ::disabled children)
      | _ =>
        ReasonReact.createDomElement tag props::{"className": classNames, "href": "#"} children
      }
    }
  };
};

module Menu = {
  /* TODO: Support Context someday */
  let component = ReasonReact.statelessComponent "Dropdown.Menu";
  let make
      tag::(tag: string)="div"
      right::(right: bool)=false
      isOpen::(isOpen: bool)
      classname::(classname: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classNames =
        ["dropdown-menu", right ? "dropdown-menu-right" : "", unwrapStr i classname]
        |> String.concat " ";
      ReasonReact.createDomElement
        tag
        props::{
          "className": classNames,
          "tabIndex": "-1",
          "aria-hidden": Js.Boolean.to_js_boolean (not isOpen),
          "role": "menu"
        }
        children
    }
  };
};

module Divider = {
  let component = ReasonReact.statelessComponent "Dropdown.Divider";
  let make children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement "div" props::{"className": "dropdown-divider"} children
  };
};

module Header = {
  let component = ReasonReact.statelessComponent "Dropdown.Header";
  let make children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement "h6" props::{"className": "dropdown-header"} children
  };
};

module Item = {
  let component = ReasonReact.statelessComponent "Dropdown.Item";
  let make
      disabled::(disabled: bool)=false
      toggle::(toggle: bool)=true
      active::(active: bool)=true
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      href::(href: option string)=?
      classname::(classname: option string)=?
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
      let tabIndex = disabled ? "-1" : "0";
      let tag =
        switch href {
        | None => "button"
        | Some _ => "a"
        };
      let _type =
        switch (onClick, tag) {
        | (Some _, "button") => Some "button"
        | (_, _) => None
        };
      let classes =
        ["dropdown-item", active ? "active" : "", disabled ? "disabled" : ""] |> String.concat " ";
      ReasonReact.createDomElement
        tag
        props::{
          "className": classes,
          "tabIndex": tabIndex,
          "onClick": self.handle click,
          "type": Js.Null_undefined.from_opt _type,
          "href": Js.Null_undefined.from_opt href
        }
        children
    }
  };
};