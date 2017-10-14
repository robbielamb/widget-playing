/* TODO: Dropdown Size. Make the dropdown toggle when off the menu is clicked. */

include Utils;

module Color = ButtonRe.Color;

module Size = ButtonRe.Size;

type retainedProps = {isOpen: bool};

let component = ReasonReact.statelessComponent "Dropdown";

let make
    tag::(tag: string)="div"
    disabled::(disabled: bool)=false
    group::(group: bool)=false
    isOpen::(isOpen: bool)=false
    toggle::(toggle: option (unit => unit))=?
    classname::(classname: option string)=?
    children => {
  ...component,
  render: fun _self => {
    let classNames =
      [group ? "btn-group" : "dropdown", isOpen ? "show" : "", unwrapStr i classname]
      |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classNames} children
  }
};

module Toggle = {
  type retainedProps = {
    nav: bool,
    onClick: option (ReactEventRe.Mouse.t => unit),
    toggle: unit => unit,
    disabled: bool,
    tag: option string
  };
  let handleOnClick
      event
      (self: ReasonReact.self ReasonReact.stateless retainedProps ReasonReact.actionless) => {
    let props = self.retainedProps;
    Js.log "onClicking";
    props.disabled ?
      ReactEventRe.Mouse.preventDefault event :
      {
        if (props.nav && props.tag === None) {
          ReactEventRe.Mouse.preventDefault event
        };
        switch props.onClick {
        | None => ()
        | Some cb => cb event
        };
        let _ = props.toggle ();
        ()
      }
  };
  let component = ReasonReact.statelessComponentWithRetainedProps "Dropdown.Toggle";
  let make
      tag::(tag: option string)=?
      caret::(caret: bool)=false
      disabled::(disabled: bool)=false
      right::(right: bool)=false
      isOpen::(isOpen: bool)
      split::(split: bool)=false
      color::(color: Color.t)=Color.Secondary
      nav::(nav: bool)=false
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      toggle::(toggle: unit => unit)
      classname::(classname: option string)=?
      children => {
    ...component,
    retainedProps: {onClick, disabled, tag, nav, toggle},
    render:
      fun (self: ReasonReact.self ReasonReact.stateless retainedProps ReasonReact.actionless) => {
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
        ReasonReact.element (
          ButtonRe.make
            ::color className::classNames onClick::(self.handle handleOnClick) ::disabled 
            ariaHaspopup::true ariaExpanded::(isOpen) children
        )
      | _ =>
        ReasonReact.createDomElement
          tag
          props::{"className": classNames, "href": "#", "onClick": self.handle handleOnClick}
          children
      }
    }
  };
};

module Menu = {
  /* TODO: Support Context someday */
  let component = ReasonReact.statelessComponent "Dropdown.Menu";
  let make
      tag::(tag: string)="div"
      alignRight::(alignRight: bool)=false
      isOpen::(isOpen: bool)
      classname::(classname: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classNames =
        ["dropdown-menu", alignRight ? "dropdown-menu-right" : "", isOpen ? "show" : 
        "", unwrapStr i classname]
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
      active::(active: bool)=false
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
        ["dropdown-item", active ? "active" : "", disabled ? "disabled" : "", unwrapStr i classname] |> String.concat " ";
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