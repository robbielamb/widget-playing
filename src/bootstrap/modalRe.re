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
  el: ref (option Dom.element),
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
    children => {
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
        let document = Webapi.Dom.document;
        let el = document |> Webapi.Dom.Document.createElement "div";
        Webapi.Dom.Element.setAttribute "tabIndex" "-1" el;
        /* Webapi.Dom.CssStyleDeclaration.t; */
        /* Webapi; */
        let style = el |> Webapi.Dom.Element.asHtmlElement |> unwrapUnsafely |> Webapi.Dom.HtmlElement.style;       
        Webapi.Dom.CssStyleDeclaration.setProperty "position" "relative" "" style;
        Webapi.Dom.CssStyleDeclaration.setProperty "zIndex" (string_of_int zIndex) "" style;
     
        self.state.el := Some el;
        let _ =
          document |> Webapi.Dom.Document.asHtmlDocument |>
          andThen Webapi.Dom.HtmlDocument.body |>
          map (Webapi.Dom.Element.appendChild el);
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
    let document = Webapi.Dom.document;
    switch !self.state.el {
    | Some node =>
      let _ =
        document |> Webapi.Dom.Document.asHtmlDocument |>
        andThen Webapi.Dom.HtmlDocument.body |>
        map (Webapi.Dom.Element.removeChild node);
      ()
    | None => ()
    }
  },
  reducer: fun _action state =>
    ReasonReact.Update {...state, isBodyOverflowing: not state.isBodyOverflowing},
  render: fun (_self: ReasonReact.self state retainedProps actions) => {
    not isOpen ? ReasonReact.nullElement : {
    let content = ReasonReact.createDomElement "div" props::{"className": "modal-content"} children;
    let dialog = ReasonReact.createDomElement "div" props::{"className": "modal-dialog", "role": "document"} [|content|];

    let classNames = ["modal fade", isOpen ? "show" : ""] |> String.concat " ";
    let style = ReactDOMRe.Style.make display::(isOpen ? "block" : "none") ();
    ReasonReact.createDomElement "div" props::{"className": classNames, "role": "dialog", "style":style, "tabIndex":"-1"} [|dialog|];
    }
  }
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