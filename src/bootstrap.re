type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let unwrapValue =
  fun
  | `String s => toJsUnsafe s
  | `Bool b => toJsUnsafe (Js.Boolean.to_js_boolean b)
  | `Float f => toJsUnsafe f
  | `Date d => toJsUnsafe d
  | `Callback c => toJsUnsafe c
  | `Element e => toJsUnsafe e
  | `Object o => toJsUnsafe o
  | `Enum _ => assert false;

let optionMap fn option =>
  switch option {
  | Some value => Some (fn value)
  | None => None
  };

module Size = {
  type t =
    | SM
    | LG
    | XL;
  let toString size =>
    switch size {
    | SM => "sm"
    | LG => "lg"
    | XL => "xl"
    };
};

module Alert = {
  external alert : ReasonReact.reactClass = "Alert" [@@bs.module "reactstrap"];
  module Color = {
    type t =
      | Primary
      | Success
      | Info
      | Warning
      | Danger;
    let toString color =>
      switch color {
      | Primary => "primary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      };
  };
  let make
      className::(className: option string)=?
      color::(color: Color.t)=Color.Success
      isOpen::(isOpen: bool)=true
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      ::transitionAppearTimeout=150
      ::transitionEnterTimeout=150
      ::transitionLeaveTimeout=150
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::alert
      props::{
        "className": Js.Null_undefined.from_opt className,
        "color": Color.toString color,
        "isOpen": Js.Boolean.to_js_boolean isOpen,
        "toggle": Js.Null_undefined.from_opt toggle,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "transitionAppearTimeout": transitionAppearTimeout,
        "transitionEnterTimeout": transitionEnterTimeout,
        "transitionLeaveTimeout": transitionLeaveTimeout,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Badge = {
  external badge : ReasonReact.reactClass = "Badge" [@@bs.module "reactstrap"];
  module Color = {
    type t =
      | Default
      | Primary
      | Success
      | Info
      | Warning
      | Danger;
    let toString color =>
      switch color {
      | Default => "default"
      | Primary => "primary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      };
  };
  let make
      color::(color: Color.t)=Color.Default
      pill::(pill: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::badge
      props::{
        "color": Color.toString color,
        "pill": Js.Boolean.to_js_boolean pill,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module BreadCrumb = {
  external breadCrumb : ReasonReact.reactClass = "Breadcrumb" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::breadCrumb
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module BreadCrumbItem = {
  external breadCrumbItem : ReasonReact.reactClass = "BreadcrumbItem" [@@bs.module "reactstrap"];
  let make
      active::(active: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::breadCrumbItem
      props::{
        "active": Js.Boolean.to_js_boolean active,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Button = {
  external button : ReasonReact.reactClass = "Button" [@@bs.module "reactstrap"];
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
  let make
      active::(active: bool)=false
      block::(block: bool)=false
      color::(color: Color.t)=Color.Secondary
      disabled::(disabled: bool)=false
      getRef::(getRef: option [ | `String string | `Element ReasonReact.reactElement])=?
      outline::(outline: bool)=false
      size::(size: option Size.t)=?
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::button
      props::{
        "active": Js.Boolean.to_js_boolean active,
        "block": Js.Boolean.to_js_boolean block,
        "color": Color.toString color,
        "disabled": Js.Boolean.to_js_boolean disabled,
        "getRef": Js.Null_undefined.from_opt (optionMap unwrapValue getRef),
        "outline": Js.Boolean.to_js_boolean outline,
        "onClick": Js.Null_undefined.from_opt onClick,
        "size": optionMap Size.toString size,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module ButtonDropDown = {};

module ButtonGroup = {};

module ButtonToolbar = {};

module DropDownToggle = {};

module DropdownMenu = {};

module DropdownItem = {};

module Modal = {
  external modal : ReasonReact.reactClass = "Modal" [@@bs.module "reactstrap"];
  let make
      isOpen::(isOpen: bool)=false
      autoFocus::(autoFocus: bool)=true
      size::(size: option string)=?
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      keyboard::(keyboard: bool)=true
      role::(role: option string)=?
      labelledBy::(labelledBy: option string)=?
      backdrop::(backdrop: bool)=true
      onEnter::(onEnter: option (unit => unit))=?
      onExit::(onExit: option (unit => unit))=?
      onOpened::(onOpened: option (unit => unit))=?
      onClosed::(onClosed: option (unit => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      props::{
        "isOpen": Js.Boolean.to_js_boolean isOpen,
        "autoFocus": Js.Boolean.to_js_boolean autoFocus,
        "size": Js.Null_undefined.from_opt size,
        "toggle": Js.Null_undefined.from_opt toggle,
        "keyboard": Js.Boolean.to_js_boolean keyboard,
        "role": Js.Null_undefined.from_opt role,
        "labelledBy": Js.Null_undefined.from_opt labelledBy,
        "backdrop": Js.Boolean.to_js_boolean backdrop,
        "onEnter": Js.Null_undefined.from_opt onEnter,
        "onExit": Js.Null_undefined.from_opt onExit,
        "onOpened": Js.Null_undefined.from_opt onOpened,
        "onClosed": Js.Null_undefined.from_opt onClosed,
        
      }
      reactClass::modal
      children;
};

module ModalHeader = {
  external modalHeader : ReasonReact.reactClass = "ModalHeader" [@@bs.module "reactstrap"];
};

module ModalBody = {
  external modalBode : ReasonReact.reactClass = "ModalBody" [@@bs.module "reactstrap"];
};

module ModalFooter = {
  external modalFooter : ReasonReact.reactClass = "ModalFooter" [@@bs.module "reactstrap"];
};

/* Layout items */
module Container = {
  external container : ReasonReact.reactClass = "Container" [@@bs.module "reactstrap"];
  let make
      fluid::(fluid: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::container
      props::{
        "fluid": Js.Boolean.to_js_boolean fluid,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Row = {
  external row : ReasonReact.reactClass = "Row" [@@bs.module "reactstrap"];
  let make
      noGutters::(noGutters: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::row
      props::{
        "noGutters": Js.Boolean.to_js_boolean noGutters,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Col = {
  external col : ReasonReact.reactClass = "Col" [@@bs.module "reactstrap"];
  type shape = Js.t {. size : int, push : int, pull : int, offset : int};
  type columnProps = option [ | `String string | `Object shape];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      xs::(xs: columnProps)=?
      sm::(sm: columnProps)=?
      md::(md: columnProps)=?
      lg::(lg: columnProps)=?
      xl::(xl: columnProps)=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::col
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "xs": Js.Null_undefined.from_opt (optionMap unwrapValue xs),
        "sm": Js.Null_undefined.from_opt (optionMap unwrapValue sm),
        "md": Js.Null_undefined.from_opt (optionMap unwrapValue md),
        "lg": Js.Null_undefined.from_opt (optionMap unwrapValue lg),
        "xl": Js.Null_undefined.from_opt (optionMap unwrapValue xl),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Jumbotron = {
  external jumbotron : ReasonReact.reactClass = "Jumbotron" [@@bs.module "reactstrap"];
  let make
      fluid::(fluid: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::jumbotron
      props::{
        "fluid": Js.Boolean.to_js_boolean fluid,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};