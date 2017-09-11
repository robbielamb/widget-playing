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
  let make1
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
  let component = ReasonReact.statelessComponent "Alert";
  let make
      className::(className: option string)=?
      closeClassName::(closeClassName: option string)=?
      color::(color: Color.t)=Color.Success
      isOpen::(isOpen: bool)=true
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      tag::(tag: string)="div"
      closeAriaLabel::(closeAriaLabel: string)="Close"
      ::transitionAppearTimeout=150
      ::transitionEnterTimeout=150
      ::transitionLeaveTimeout=150
      cssModule::(cssModule: option (Js.t {..}))=?
      children => {
    ...component,
    render: fun _self => {
      let closeClasses = classNameReduce closeClassName [cn "close"];
      let (toggleElement, toggleEnabled) =
        switch toggle {
        | None => (ReasonReact.nullElement, false)
        | Some cb => (
            ReasonReact.createDomElement
              "button"
              props::{"type": "button", "className": closeClasses, "onClick": cb, "aria-label": closeAriaLabel}
              [|
                ReasonReact.createDomElement
                  "span"
                  props::{"aria-hidden": "true"}
                  [|ReasonReact.stringToElement (Js.String.fromCharCode 215)|]
              |],
            true
          )
        };
      let _ = Js.Array.unshift toggleElement children;
      let classes = classNameReduce className [cn "alert", cn ("alert-" ^ Color.toString color)];
      let alert = ReasonReact.createDomElement tag props::{"className": classes} children;
      
      <Transition.CSSTransition> alert </Transition.CSSTransition>
    }
  };
};

module Badge = {
  module Color = {
    type t =
      | Primary
      | Secondary
      | Success
      | Info
      | Warning
      | Danger
      | Dark
      | Light;
    let toString color =>
      switch color {
      | Primary => "primary"
      | Secondary => "secondary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      | Dark => "dark"
      | Light => "light"
      };
  };
  let component = ReasonReact.statelessComponent "Badge";
  let make
      color::(color: Color.t)=Color.Secondary
      pill::(pill: bool)=false
      secondary::(secondary: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      href::(href: option string)=?
      /*  cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self => {
      let tag =
        switch href {
        | None => tag
        | Some _ => tag == "div" ? "a" : tag
        };
      let badgeColor = "badge-" ^ Color.toString color;
      let classes =
        classNameReduce
          className
          [
            cn "badge",
            cn badgeColor,
            ocn ("badge-pill", pill),
            ocn ("badge-secondary", secondary)
          ];
      ReasonReact.createDomElement
        tag props::{"className": classes, "href": Js.Null_undefined.from_opt href} children
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

/* module Modal = {
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
   }; */
module ModalHeader = {
  let component = ReasonReact.statelessComponent "ModalHeader";
  let make
      tag::(tag: string)="h4"
      wrapTag::(wrapTag: string)="div"
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      className::(className: option string)=?
      cssModule::(cssModule: option (Js.t {..}))=?
      closeAriaLabel::(closeAriaLabel: string)="Close"
      children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "modal-header"];
      let closeButton =
        switch toggle {
        | None => ReasonReact.nullElement
        | Some cb =>
          ReasonReact.createDomElement
            "button"
            props::{
              "type": "button",
              "onClick": cb,
              "className": "close",
              "aria-label": closeAriaLabel
            }
            [|
              ReasonReact.createDomElement
                "span"
                props::{"aria-hidden": "true"}
                [|ReasonReact.stringToElement (Js.String.fromCharCode 215)|]
            |]
        };
      let inner = ReasonReact.createDomElement tag props::{"className": "modal-title"} children;
      ReasonReact.createDomElement wrapTag props::{"className": classes} [|inner, closeButton|]
    }
  };
};

module ModalBody = {
  let component = ReasonReact.statelessComponent "ModalBody";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement
        tag props::{"className": classNameReduce className [cn "modal-body"]} children
  };
};

module ModalFooter = {
  let component = ReasonReact.statelessComponent "ModalFooter";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement
        tag props::{"className": classNameReduce className [cn "modal-footer"]} children
  };
};

module Nav = {
  /* This could have more option and classes applied! */
  let component = ReasonReact.statelessComponent "ModalFooter";
  let make
      tabs::(tabs: bool)=false
      pills::(pills: bool)=false
      vertical::(vertical: bool)=false
      justified::(justified: bool)=false
      navbar::(navbar: bool)=false
      tag::(tag: string)="ul"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes =
        classNameReduce
          className
          [
            ocn ("navbar-nav", navbar),
            ocn ("nav", not navbar),
            ocn ("nav-tabs", tabs),
            ocn ("nav-pills", pills),
            ocn ("nav-justified", justified),
            ocn ("flex-column", vertical)
          ];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

/* module NavDropdown = {
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
   }; */
module NavItem = {
  let component = ReasonReact.statelessComponent "NavItem";
  let make
      tag::(tag: string)="li"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "nav-item"];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module NavLink = {
  let component = ReasonReact.statelessComponent "NavLink";
  let make
      tag::(tag: string)="a"
      getRef::(getRef: option [ | `String string | `Element ReasonReact.reactElement])=?
      disabled::(disabled: bool)=false
      active::(active: bool)=false
      className::(className: option string)=?
      onClick::(onClick: option (ReactEventRe.Mouse.t => unit))=?
      href::(href: option string)=?
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
      let classes =
        classNameReduce
          className [cn "nav-link", ocn ("disabled", disabled), ocn ("active", active)];
      ReasonReact.createDomElement
        tag
        props::{
          "className": classes,
          "onClick": self.handle click,
          "href": Js.Null_undefined.from_opt href
        }
        children
    }
  };
};

module Navbar = {
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
  let component = ReasonReact.statelessComponent "NavBar";
  let make
      light::(light: bool)=false
      inverse::(inverse: bool)=false
      full::(full: bool)=false
      fixed::(fixed: option Fixed.t)=?
      sticky::(sticky: option string)=?
      color::(color: option Color.t)=?
      role::(role: option string)=?
      tag::(tag: string)="nav"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      toggleable::(toggleable: bool)=false
      children => {
    ...component,
    render: fun _self => {
      let bgColor (cls: option 'a) =>
        switch cls {
        | None => ocn ("", false)
        | Some x => ocn ("bg-" ^ Color.toString x, true)
        };
      let fixedClass (cls: option 'b) =>
        switch cls {
        | None => ocn ("", false)
        | Some x => ocn ("fixed-" ^ Fixed.toString x, true)
        };
      let stickyClass (cls: option 'c) =>
        switch cls {
        | None => ocn ("", false)
        | Some x => ocn ("sticky-" ^ x, true)
        };
      let classes =
        classNameReduce
          className
          [
            cn "navbar",
            ocn ("navbar-toggleable", toggleable),
            ocn ("navbar-light", light),
            ocn ("navbar-inverse", inverse),
            ocn ("navbar-full", full),
            bgColor color,
            fixedClass fixed,
            stickyClass sticky
          ];
      ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
    }
  };
};

module NavbarBrand = {
  let component = ReasonReact.statelessComponent "NavbarBrand";
  let make
      tag::(tag: string)="a"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      href::(href: string)="#"
      children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "navbar-brand"];
      ReasonReact.createDomElement tag props::{"className": classes, "href": href} children
    }
  };
};

module NavbarToggler = {
  let component = ReasonReact.statelessComponent "NavbarToggler";
  let make
      tag::(tag: string)="button"
      _type::(_type: string)="button"
      className::(className: option string)=?
      right::(right: bool)=false
      left::(left: bool)=false
      children => {
    ...component,
    render: fun _self => {
      let classes =
        classNameReduce
          className
          [
            cn "navbar-toggler",
            ocn ("navbar-toggler-right", right),
            ocn ("navbar-toggler-left", left)
          ];
      ReasonReact.createDomElement tag props::{"type": _type, "className": classes} children
    }
  };
};

/* Layout items */
module Container = {
  let component = ReasonReact.statelessComponent "Container";
  let make
      fluid::(fluid: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes =
        classNameReduce className [ocn ("container-fluid", fluid), ocn ("container", not fluid)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Row = {
  /* Todo: Add more options here */
  external row : ReasonReact.reactClass = "Row" [@@bs.module "reactstrap"];
  let component = ReasonReact.statelessComponent "Row";
  let make
      noGutters::(noGutters: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "row", ocn ("no-gutters", noGutters)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Col = {
  let component = ReasonReact.statelessComponent "Col";
  type size =
    | Auto
    | Size int;
  type shape = {
    size: option size,
    push: option int,
    pull: option int,
    offset: option int
  };
  let shape
      size::(size: option size)=?
      push::(push: option int)=?
      pull::(pull: option int)=?
      offset::(offset: option int)=?
      () => {
    size,
    push,
    pull,
    offset
  };
  let genClasses (colWidth: string) (shape: shape) => {
    let isXs = "xs" == colWidth;
    let interfix = isXs ? "-" : {j|-$(colWidth)-|j};
    let colClass =
      cn (
        switch shape.size {
        | Some Auto => {j|col$(interfix)auto|j}
        | Some (Size size) => {j|col$(interfix)$(size)|j}
        | None => isXs ? "col" : {j|col-$(colWidth)|j}
        }
      );
    let formatClass name intensity => {
      let colSize = string_of_int intensity;
      {j|$(name)$(interfix)$(colSize)|j}
    };
    let colPush =
      ocn (
        switch shape.push {
        | Some push => (formatClass "push" push, true)
        | None => ("", false)
        }
      );
    let colPull =
      ocn (
        switch shape.pull {
        | Some pull => (formatClass "pull" pull, true)
        | None => ("", false)
        }
      );
    let colOffset =
      ocn (
        switch shape.offset {
        | Some offset => (formatClass "offset" offset, true)
        | None => ("", false)
        }
      );
    [colClass, colPush, colPull, colOffset]
  };
  let make
      tag::(tag: string)="div"
      xs::(xs: option shape)=(Some (shape ()))
      sm::(sm: option shape)=?
      md::(md: option shape)=?
      lg::(lg: option shape)=?
      xl::(xl: option shape)=?
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let classShapeList =
        [("xs", xs), ("sm", sm), ("md", md), ("lg", lg), ("xl", xl)] |>
        List.map (
          fun (col, maybeShape) =>
            switch maybeShape {
            | None => []
            | Some shape => genClasses col shape
            }
        ) |> List.flatten;
      let classes = classNameReduce className classShapeList;
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};

module Jumbotron = {
  let component = ReasonReact.statelessComponent "Jumbotron";
  let make
      fluid::(fluid: bool)=false
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self => {
      let classes = classNameReduce className [cn "jumbotron", ocn ("jumbotron-fluid", fluid)];
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};