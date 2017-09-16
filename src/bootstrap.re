type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let map f =>
  fun
  | Some v => Some (f v)
  | None => None;

let andThen (f: 'a => option 'b) =>
  fun
  | Some v => f v
  | None => None;

let unwrapUnsafely =
  fun
  | Some v => v
  | None => raise (Invalid_argument "Passed `None` to unwrapUnsafely");

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

/* Identity function */
let i x => x;

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

let unwrapStr f maybeStr =>
  switch maybeStr {
  | Some v => f v
  | None => ""
  };

module TextColor = {
  type t =
    | White
    | Dark
    | Muted
    | Hide
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger;
  let toString color =>
    switch color {
    | White => "white"
    | Dark => "dark"
    | Muted => "muted"
    | Hide => "hide"
    | Primary => "primary"
    | Secondary => "secondary"
    | Success => "success"
    | Info => "info"
    | Warning => "warning"
    | Danger => "danger"
    };
  let unWrap = unwrapStr toString;
};

module BackgroundColor = {
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
    "bg-" ^ (
      switch color {
      | Primary => "primary"
      | Secondary => "secondary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      | Dark => "dark"
      | Light => "light"
      | White => "white"
      | Transparent => "transparent"
      }
    );
  let unWrap = unwrapStr toString;
};

module BorderColor = {
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
    "border-" ^ (
      switch color {
      | Primary => "primary"
      | Secondary => "secondary"
      | Success => "success"
      | Info => "info"
      | Warning => "warning"
      | Danger => "danger"
      | Dark => "dark"
      | Light => "light"
      | White => "white"
      | Transparent => "transparent"
      }
    );
  let unWrap = unwrapStr toString;
};

module Alert = {
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
  let onEnter _el _isAppearing => Js.log "onEnter";
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
              props::{
                "type": "button",
                "className": closeClasses,
                "onClick": cb,
                "aria-label": closeAriaLabel
              }
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
      let visible = isOpen ? alert : <span />;
      /* visible */
      let fade = "fade";
      let show = "show";
      visible
      /* TODO: Make this work with an animation */
      /* <Transition.Transition
            onEnter=(onEnter)
            timeout=500 _in=isOpen>
           visible
         </Transition.Transition> */
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

module ButtonGroup = {
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
  let component = ReasonReact.statelessComponent "ButtonGroup";
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

module ButtonToolbar = {
  let component = ReasonReact.statelessComponent "ButtonToolbar";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      role::(role: string)="toolbar"
      children => {
    let classes = classNameReduce className [cn "btn-toolbar"];
    ReasonReact.createDomElement tag props::{"className": classes, "role": role} children
  };
};

module Card = {
  let component = ReasonReact.statelessComponent "Card";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      color::(color: option TextColor.t)=?
      backgroundColor::(backgroundColor: option BackgroundColor.t)=?
      borderColor::(borderColor: option BorderColor.t)=?
      children => {
    let classes =
      [
        "card",
        unwrapStr i className,
        TextColor.unWrap color,
        BackgroundColor.unWrap backgroundColor,
        BorderColor.unWrap borderColor
      ] |>
      String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardBody = {
  let component = ReasonReact.statelessComponent "CardBody";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = ["card-body", unwrapStr i className] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardColumns = {
  let component = ReasonReact.statelessComponent "CardColumns";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = [unwrapStr i className, "card-columns"] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardDeck = {
  let component = ReasonReact.statelessComponent "CardDeck";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-deck"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardFooter = {
  let component = ReasonReact.statelessComponent "CardFooter";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-footer"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardGroup = {
  let component = ReasonReact.statelessComponent "CardGroup";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-group"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardHeader = {
  let component = ReasonReact.statelessComponent "CardHeader";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-header"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardImg = {
  module Fixed = {
    type t =
      | None
      | Top
      | Bottom;
    let toString fixed =>
      switch fixed {
      | None => ""
      | Top => "-top"
      | Bottom => "-bottom"
      };
  };
  let component = ReasonReact.statelessComponent "CardImg";
  let make
      tag::(tag: string)="img"
      src::(src: string)=""
      alt::(alt: string)=""
      fixed::(fixed: Fixed.t)=None
      className::(className: option string)=?
      children => {
    let classes = classNameReduce className [cn ("card-img" ^ Fixed.toString fixed)];
    ReasonReact.createDomElement tag props::{"className": classes, "src": src, "alt": alt} children
  };
};

module CardImgOverlay = {
  let component = ReasonReact.statelessComponent "CardImgOverlay";
  let make tag::(tag: string)="div" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-img-overlay"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardLink = {
  /* TODO: Handle href and proper callbacks */
  let component = ReasonReact.statelessComponent "CardLink";
  let make tag::(tag: string)="a" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-link"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CardTitle = {
  let component = ReasonReact.statelessComponent "CardTitle";
  let make tag::(tag: string)="h4" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-title"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CartSubtitle = {
  let component = ReasonReact.statelessComponent "CardSubTitle";
  let make tag::(tag: string)="h6" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-subtitle"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module CartText = {
  let component = ReasonReact.statelessComponent "CardText";
  let make tag::(tag: string)="p" className::(className: option string)=? children => {
    let classes = classNameReduce className [cn "card-text"];
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

/* module Collapse = {
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
   }; */
module DropDownToggle = {};

module DropdownMenu = {};

module DropdownItem = {};

module Fade = {
  /*   let component = ReasonReact.statelessComponent "Fade";

       let make _in::(_in: bool)=false timeout::(timeout: int)=300 mountOnEnter::(mountOnEnter: bool)=false mountOnExit::(mountOnExit: bool)=false children => {
         Transition.Transition.make enteredClassName="in" children;
       }; */
};

module Form = {
  let component = ReasonReact.statelessComponent "Form";
  let make
      tag::(tag: string)="form"
      inline::(inline: bool)=false
      className::(className: option string)=?
      children => {
    let classes = [unwrapStr i className, inline ? "form-inline" : ""] |> String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module FormFeedback = {};

module FormGroup = {
  /* TODO: Finish form-group and form-check */
  let component = ReasonReact.statelessComponent "FormGroup";
  let make
      tag::(tag: string)="div"
      row::(row: bool)=false
      check::(check: bool)=false
      disabled::(disabled: bool)=false
      inline::(inline: bool)=false
      className::(className: option string)=?
      children => {
    let classes =
      [
        unwrapStr i className,
        row ? "row" : "",
        check ? "form-check" : "form-group",
        check && disabled ? "disabled" : "",
        check && inline ? "form-check-inline" : ""
      ] |>
      String.concat " ";
    ReasonReact.createDomElement tag props::{"className": classes} children
  };
};

module FormText = {
  let component = ReasonReact.statelessComponent "FormText";

  let make
  tag::(tag: string)="small"
  inline::(inline: bool)=false
  color::(color: option TextColor.t)=?
  className::(className: option string)=?
  children => {
let classes =
  [
    unwrapStr i className,
    not inline ? "form-text" : "",
    TextColor.unWrap color
  ] |>
  String.concat " ";
ReasonReact.createDomElement tag props::{"className": classes} children
  }; 
};

module Modal = {
  type actions =
    | BackgroundClick;
  type state = {
    el: ref (option Dom.htmlElement),
    isBodyOverflowing: bool
  };
  type retainedProps = {isOpen: bool};
  let component = ReasonReact.reducerComponentWithRetainedProps "Modal";
  let make
      isOpen::(isOpen: bool)=false
      autoFocus::(autoFocus: bool)=true
      size::(size: option string)=?
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      keyboard::(keyboard: bool)=true
      role::(role: string)="dialog"
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
      zIndex::(zIndex: int)=1050
      /* backdropTransitionTimeout::(backdropTransitionTimeout: option int)=?
         backdropTransitionAppearTimeout::(backdropTransitionAppearTimeout: option int)=?
         backdropTransitionEnterTimeout::(backdropTransitionEnterTimeout: option int)=?
         backdropTransitionLeaveTimeout::(backdropTransitionLeaveTimeout: option int)=?
         modalTransitionTimeout::(modalTransitionTimeout: option int)=?
         modalTransitionAppearTimeout::(modalTransitionAppearTimeout: option int)=?
         modalTransitionEnterTimeout::(modalTransitionEnterTimeout: option int)=?
         modalTransitionLeaveTimeout::(modalTransitionLeaveTimeout: option int)=? */
      _children => {
    ...component,
    retainedProps: {isOpen: isOpen},
    initialState: fun () => {el: ref None, isBodyOverflowing: false},
    didMount: fun self =>
      ReasonReact.SideEffects (
        fun _self => {
          isOpen ? () : /** toggle portal */ ();
          switch onEnter {
          | Some cb => cb ()
          | None => ()
          };
          let document = Bs_webapi.Dom.document;
          let foo = document |> Bs_webapi.Dom.Document.createElement "div";
          Bs_webapi.Dom.Element.setAttribute "tabIndex" "-1" foo;
          /* Bs_webapi.Dom.CssStyleDeclaration.t; */
          /* Bs_webapi; */
          let foo = foo |> Bs_webapi.Dom.Element.asHtmlElement |> unwrapUnsafely;
          let style = Bs_webapi.Dom.HtmlElement.style foo;
          Bs_webapi.Dom.CssStyleDeclaration.setProperty "position" "relative" "" style;
          Bs_webapi.Dom.CssStyleDeclaration.setProperty "zIndex" (string_of_int zIndex) "" style;
          self.state.el := Some foo;
          let _ =
            document |> Bs_webapi.Dom.Document.asHtmlDocument |>
            andThen Bs_webapi.Dom.HtmlDocument.body |>
            map (Bs_webapi.Dom.Element.appendChild foo);
          ()
        }
      ),
    /* willReceiveProps: fun self => self.state, */
    /* shouldUpdate: fun {oldSelf, newSelf} => (oldSelf.retainedProps.isOpen === newSelf.retainedProps.isOpen) ? true : false, */
    /* willUpdate: fun _oldAndNewSelf => (), */
    didUpdate: fun {oldSelf, newSelf} =>
      if (oldSelf.retainedProps.isOpen === newSelf.retainedProps.isOpen) {
        Js.log "NoChange"
      },
    willUnmount: fun self => {
      let document = Bs_webapi.Dom.document;
      switch !self.state.el {
      | Some node =>
        let _ =
          document |> Bs_webapi.Dom.Document.asHtmlDocument |>
          andThen Bs_webapi.Dom.HtmlDocument.body |>
          map (Bs_webapi.Dom.Element.removeChild node);
        ()
      | None => ()
      }
    },
    reducer: fun _action state =>
      ReasonReact.Update {...state, isBodyOverflowing: not state.isBodyOverflowing},
    render: fun self => <span onClick=(self.reduce (fun _self => BackgroundClick)) />
  };
  ReactDOMRe.render;
};

module ModalHeader = {
  let component = ReasonReact.statelessComponent "ModalHeader";
  let make
      tag::(tag: string)="h4"
      wrapTag::(wrapTag: string)="div"
      toggle::(toggle: option (ReactEventRe.Mouse.t => unit))=?
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
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
      let classes =
        ["jumbotron", fluid ? "jumbotron-fluid" : "", unwrapStr i className] |> String.concat " ";
      ReasonReact.createDomElement tag props::{"className": classes} children
    }
  };
};