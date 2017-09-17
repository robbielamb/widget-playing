include Utils;

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

module Header = {
  let component = ReasonReact.statelessComponent "Modal.Header";
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

module Body = {
  let component = ReasonReact.statelessComponent "Modal.Body";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement
        tag props::{"className": String.concat " " ["modal-body", unwrapStr i className]} children
  };
};

module Footer = {
  let component = ReasonReact.statelessComponent "Modal.Footer";
  let make
      tag::(tag: string)="div"
      className::(className: option string)=?
      /* cssModule::(cssModule: option (Js.t {..}))=? */ children => {
    ...component,
    render: fun _self =>
      ReasonReact.createDomElement
        tag
        props::{"className": String.concat " " ["modal-footer", unwrapStr i className]}
        children
  };
};