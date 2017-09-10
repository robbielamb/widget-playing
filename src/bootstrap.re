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

let cn c => Classnames.Classname c;

let ocn c => Classnames.Option c;

let classNameReduce (baseClass: option string) (classList: list Classnames.t) => {
  let baseClass =
    switch baseClass {
    | Some name => [cn name]
    | None => []
    };
  List.rev_append baseClass classList |> Classnames.classNames
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
  let component = ReasonReact.statelessComponent "Badge";
  let make
      color::(color: Color.t)=Color.Default
      pill::(pill: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /*  cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self => {
      let badgeColor = "badge-" ^ Color.toString color;
      let classes =
        classNameReduce className [cn "badge", cn badgeColor, ocn ("badge-pill", pill)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module BreadCrumb = {
  let breadCrumb = ReasonReact.statelessComponent "BreadCrumb";
  let make
      tag::(tag: string)="ol"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...breadCrumb,
    render: fun _self => {
      let classes = classNameReduce className [cn "breadcrumb"];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module BreadCrumbItem = {
  let breadCrumbItem = ReasonReact.statelessComponent "BreadCrumbItem";
  let make
      active::(active: bool)=false
      tag::(tag: string)="li"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...breadCrumbItem,
    render: fun _self => {
      let classes = classNameReduce className [cn "breadcrumb-item", ocn ("active", active)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
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
        "size": Js.Null_undefined.from_opt (optionMap Size.toString size),
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module ButtonDropDown = {};

module ButtonGroup = {};

module ButtonToolbar = {};

module Collapse = {
  external collapse : ReasonReact.reactClass = "Collapse" [@@bs.module "reactstrap"];
  type delayShape = Js.t {. show : int, hide : int};
  type delayProps = option [ | `Float float | `Object delayShape];
  let make
      isOpen::(isOpen: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      navbar::(navbar: bool)=false
      delay::(delay: delayProps)=?
      onOpen::(onOpen: option (unit => unit))=?
      onClosed::(onClosed: option (unit => unit))=?
      children =>
    ReasonReact.wrapJsForReason
      props::{
        "isOpen": Js.Boolean.to_js_boolean isOpen,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "navbar": Js.Boolean.to_js_boolean navbar,
        "delay": Js.Null_undefined.from_opt (optionMap unwrapValue delay),
        "onOpen": Js.Null_undefined.from_opt onOpen,
        "onClosed": Js.Null_undefined.from_opt onClosed
      }
      children;
};

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
      className::(className: option string)=?
      wrapClassName::(wrapClassName: option string)=?
      modalClassName::(modalClassName: option string)=?
      backdropClassName::(backdropClassName: option string)=?
      contentClassName::(contentClassName: option string)=?
      fade::(fade: bool)=true
      cssModule::(cssModule: option (Js.t {..}))=?
      zIndex::(zIndex: option int)=?
      backdropTransitionTimeout::(backdropTransitionTimeout: option int)=?
      backdropTransitionAppearTimeout::(backdropTransitionAppearTimeout: option int)=?
      backdropTransitionEnterTimeout::(backdropTransitionEnterTimeout: option int)=?
      backdropTransitionLeaveTimeout::(backdropTransitionLeaveTimeout: option int)=?
      modalTransitionTimeout::(modalTransitionTimeout: option int)=?
      modalTransitionAppearTimeout::(modalTransitionAppearTimeout: option int)=?
      modalTransitionEnterTimeout::(modalTransitionEnterTimeout: option int)=?
      modalTransitionLeaveTimeout::(modalTransitionLeaveTimeout: option int)=?
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
        "className": Js.Null_undefined.from_opt className,
        "wrapClassName": Js.Null_undefined.from_opt wrapClassName,
        "modalClassName": Js.Null_undefined.from_opt modalClassName,
        "backdropClassName": Js.Null_undefined.from_opt backdropClassName,
        "contentClassName": Js.Null_undefined.from_opt contentClassName,
        "fade": Js.Boolean.to_js_boolean fade,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "zIndex": Js.Null_undefined.from_opt zIndex,
        "backdropTransitionTimeout": Js.Null_undefined.from_opt backdropTransitionTimeout,
        "backdropTransitionAppearTimeout":
          Js.Null_undefined.from_opt backdropTransitionAppearTimeout,
        "backdropTransitionEnterTimeout": Js.Null_undefined.from_opt backdropTransitionEnterTimeout,
        "backdropTransitionLeaveTimeout": Js.Null_undefined.from_opt backdropTransitionLeaveTimeout,
        "modalTransitionTimeout": Js.Null_undefined.from_opt modalTransitionTimeout,
        "modalTransitionAppearTimeout": Js.Null_undefined.from_opt modalTransitionAppearTimeout,
        "modalTransitionEnterTimeout": Js.Null_undefined.from_opt modalTransitionEnterTimeout,
        "modalTransitionLeaveTimeout": Js.Null_undefined.from_opt modalTransitionLeaveTimeout
      }
      reactClass::modal
      children;
};

module ModalHeader = {
  external modalHeader : ReasonReact.reactClass = "ModalHeader" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      wrapTag::(wrapTag: option [ | `String string | `Element ReasonReact.reactElement])=?
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      closeAriaLabel::(closeAriaLabel: option string)=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::modalHeader
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "wrapTag": Js.Null_undefined.from_opt (optionMap unwrapValue wrapTag),
        "toggle": Js.Null_undefined.from_opt toggle,
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "closeAriaLabel": Js.Null_undefined.from_opt closeAriaLabel
      }
      children;
};

module ModalBody = {
  external modalBody : ReasonReact.reactClass = "ModalBody" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::modalBody
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module ModalFooter = {
  external modalFooter : ReasonReact.reactClass = "ModalFooter" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::modalFooter
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module Nav = {
  external nav : ReasonReact.reactClass = "Nav" [@@bs.module "reactstrap"];
  let make
      tabs::(tabs: bool)=false
      pills::(pills: bool)=false
      vertical::(vertical: bool)=false
      justified::(justified: bool)=false
      navbar::(navbar: bool)=false
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::nav
      props::{
        "tabs": Js.Boolean.to_js_boolean tabs,
        "pills": Js.Boolean.to_js_boolean pills,
        "vertical": Js.Boolean.to_js_boolean vertical,
        "justified": Js.Boolean.to_js_boolean justified,
        "navbar": Js.Boolean.to_js_boolean navbar,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module NavDropdown = {
  external navDropdown : ReasonReact.reactClass = "NavDropdown" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navDropdown
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module NavItem = {
  external navItem : ReasonReact.reactClass = "NavItem" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navItem
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module NavLink = {
  external navLink : ReasonReact.reactClass = "NavLink" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      getRef::(getRef: option [ | `String string | `Element ReasonReact.reactElement])=?
      disabled::(disabled: bool)=false
      active::(active: bool)=false
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      href::(href: option string)=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navLink
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "getRef": Js.Null_undefined.from_opt (optionMap unwrapValue getRef),
        "disabled": Js.Boolean.to_js_boolean disabled,
        "active": Js.Boolean.to_js_boolean active,
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "onClick": Js.Null_undefined.from_opt onClick,
        "href": Js.Null_undefined.from_opt href
      }
      children;
};

module Navbar = {
  external navbar : ReasonReact.reactClass = "Navbar" [@@bs.module "reactstrap"];
  module Color = {
    type t =
      | Primary
      | Secondary
      | Success
      | Info
      | Warning
      | Danger
      | Light
      | Dark
      | White
      | Transparent;
    let toString color =>
      switch color {
      | Primary => "primary"
      | Secondary => "secondary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      | Light => "light"
      | Dark => "dark"
      | White => "white"
      | Transparent => "transparent"
      };
  };
  module Fixed = {
    type t =
      | Top
      | Bottom;
    let toString fixed =>
      switch fixed {
      | Top => "top"
      | Bottom => "bottom"
      };
  };
  let make
      light::(light: bool)=false
      inverse::(inverse: bool)=false
      full::(full: bool)=false
      fixed::(fixed: option Fixed.t)=?
      sticky::(sticky: option string)=?
      color::(color: option Color.t)=?
      role::(role: option string)=?
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      toggleable::(toggleable: [ | `String string | `Bool bool])=(`Bool false)
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navbar
      props::{
        "light": Js.Boolean.to_js_boolean light,
        "inverse": Js.Boolean.to_js_boolean inverse,
        "full": Js.Boolean.to_js_boolean full,
        "fixed": Js.Null_undefined.from_opt (optionMap Fixed.toString fixed),
        "sticky": Js.Null_undefined.from_opt sticky,
        "color": Js.Null_undefined.from_opt (optionMap Color.toString color),
        "role": Js.Null_undefined.from_opt role,
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "toggleable": unwrapValue toggleable
      }
      children;
};

module NavbarBrand = {
  external navbarBrand : ReasonReact.reactClass = "NavbarBrand" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navbarBrand
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule
      }
      children;
};

module NavbarToggler = {
  external navbarToggler : ReasonReact.reactClass = "NavbarToggler" [@@bs.module "reactstrap"];
  let make
      tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
      _type::(_type: option string)=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      right::(right: bool)=false
      left::(left: bool)=false
      children =>
    ReasonReact.wrapJsForReason
      reactClass::navbarToggler
      props::{
        "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
        "type": Js.Null_undefined.from_opt _type,
        "className": Js.Null_undefined.from_opt className,
        "cssModule": Js.Null_undefined.from_opt cssModule,
        "right": Js.Boolean.to_js_boolean right,
        "left": Js.Boolean.to_js_boolean left
      }
      children;
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