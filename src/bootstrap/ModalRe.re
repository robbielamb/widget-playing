include Utils;

let map = f =>
  fun
  | Some(v) => Some(f(v))
  | None => None;

let andThen = (f: 'a => option('b)) =>
  fun
  | Some(v) => f(v)
  | None => None;

let unwrapUnsafely =
  fun
  | Some(v) => v
  | None => raise(Invalid_argument("Passed `None` to unwrapUnsafely"));

type actions =
  | DidMount
  | BackgroundClick;

type state = {
  el: ref(option(Dom.element)),
  isBodyOverflowing: bool,
};

type retainedProps = {isOpen: bool};

let component = ReasonReact.reducerComponentWithRetainedProps("Modal");

let make =
    (
      ~isOpen: bool=false,
      /*       ~autoFocus: bool=true,
               ~size: option(string)=?,
               ~toggle: option((ReactEventRe.Mouse.t => unit))=?,
               ~keyboard: bool=true,
               ~role: string="dialog",
               ~labelledBy: option(string)=?,
               ~backdrop: bool=true, */
      ~onEnter: option(unit => unit)=?,
      /*       ~onExit: option((unit => unit))=?,
               ~onOpened: option((unit => unit))=?,
               ~onClosed: option((unit => unit))=?,
               ~className: option(string)=?,
               ~wrapClassName: option(string)=?,
               ~modalClassName: option(string)=?,
               ~backdropClassName: option(string)=?,
               ~contentClassName: option(string)=?,
               ~fade: bool=true, */
      ~zIndex: int=1050,
      /* backdropTransitionTimeout::(backdropTransitionTimeout: option int)=?
         backdropTransitionAppearTimeout::(backdropTransitionAppearTimeout: option int)=?
         backdropTransitionEnterTimeout::(backdropTransitionEnterTimeout: option int)=?
         backdropTransitionLeaveTimeout::(backdropTransitionLeaveTimeout: option int)=?
         modalTransitionTimeout::(modalTransitionTimeout: option int)=?
         modalTransitionAppearTimeout::(modalTransitionAppearTimeout: option int)=?
         modalTransitionEnterTimeout::(modalTransitionEnterTimeout: option int)=?
         modalTransitionLeaveTimeout::(modalTransitionLeaveTimeout: option int)=? */
      children,
    ) => {
  ...component,
  retainedProps: {
    isOpen: isOpen,
  },
  initialState: () => {el: ref(None), isBodyOverflowing: false},
  didMount: self => self.send(DidMount),
  didUpdate: ({oldSelf, newSelf}) =>
    if (oldSelf.retainedProps.isOpen === newSelf.retainedProps.isOpen) {
      Js.log("NoChange");
    },
  willUnmount: self => {
    let document = Webapi.Dom.document;
    switch (self.state.el^) {
    | Some(node) =>
      let _ =
        document
        |> Webapi.Dom.Document.asHtmlDocument
        |> andThen(Webapi.Dom.HtmlDocument.body)
        |> map(Webapi.Dom.Element.removeChild(node));
      ();
    | None => ()
    };
  },
  reducer: (action, state) =>
    switch (action) {
    | BackgroundClick =>
      ReasonReact.Update({
        ...state,
        isBodyOverflowing: !state.isBodyOverflowing,
      })
    | DidMount =>
      ReasonReact.SideEffects(
        (
          self => {
            isOpen ? () : /*** toggle portal */ ();
            switch (onEnter) {
            | Some(cb) => cb()
            | None => ()
            };
            let document = Webapi.Dom.document;
            let el = document |> Webapi.Dom.Document.createElement("div");
            Webapi.Dom.Element.setAttribute("tabIndex", "-1", el);
            let style =
              el
              |> Webapi.Dom.Element.unsafeAsHtmlElement
              /*|> unwrapUnsafely*/
              |> Webapi.Dom.HtmlElement.style;
            Webapi.Dom.CssStyleDeclaration.setProperty(
              "position",
              "relative",
              "",
              style,
            );
            Webapi.Dom.CssStyleDeclaration.setProperty(
              "zIndex",
              string_of_int(zIndex),
              "",
              style,
            );
            self.state.el := Some(el);
            let _ =
              document
              |> Webapi.Dom.Document.asHtmlDocument
              |> andThen(Webapi.Dom.HtmlDocument.body)
              |> map(Webapi.Dom.Element.appendChild(el));
            ();
          }
        ),
      )
    },
  /* Webapi.Dom.CssStyleDeclaration.t; */
  /* Webapi; */
  /* willReceiveProps: fun self => self.state, */
  /* shouldUpdate: fun {oldSelf, newSelf} => (oldSelf.retainedProps.isOpen === newSelf.retainedProps.isOpen) ? true : false, */
  render: (_self: ReasonReact.self(state, retainedProps, actions)) =>
    !isOpen ?
      ReasonReact.null :
      {
        let content =
          ReasonReact.createDomElement(
            "div",
            ~props={"className": "modal-content"},
            children,
          );
        let dialog =
          ReasonReact.createDomElement(
            "div",
            ~props={"className": "modal-dialog", "role": "document"},
            [|content|],
          );
        let classNames =
          ["modal fade", isOpen ? "show" : ""] |> String.concat(" ");
        let style =
          ReactDOMRe.Style.make(~display=isOpen ? "block" : "none", ());
        ReasonReact.createDomElement(
          "div",
          ~props={
            "className": classNames,
            "role": "dialog",
            "style": style,
            "tabIndex": "-1",
          },
          [|dialog|],
        );
      },
  /* willUpdate: fun _oldAndNewSelf => (), */
};

module Header = {
  let component = ReasonReact.statelessComponent("Modal.Header");
  let make =
      (
        ~tag: string="h4",
        ~wrapTag: string="div",
        ~toggle: option(ReactEventRe.Mouse.t => unit)=?,
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        ~closeAriaLabel: string="Close",
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["modal-header", unwrapStr(i, className)] |> String.concat(" ");
      let closeButton =
        switch (toggle) {
        | None => ReasonReact.null
        | Some(cb) =>
          ReasonReact.createDomElement(
            "button",
            ~props={
              "type": "button",
              "onClick": cb,
              "className": "close",
              "aria-label": closeAriaLabel,
            },
            [|
              ReasonReact.createDomElement(
                "span",
                ~props={"aria-hidden": "true"},
                [|ReasonReact.string(Js.String.fromCharCode(215))|],
              ),
            |],
          )
        };
      let inner =
        ReasonReact.createDomElement(
          tag,
          ~props={"className": "modal-title"},
          children,
        );
      ReasonReact.createDomElement(
        wrapTag,
        ~props={"className": classes},
        [|inner, closeButton|],
      );
    },
  };
};

module Body = {
  let component = ReasonReact.statelessComponent("Modal.Body");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        children,
      ) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        tag,
        ~props={
          "className":
            String.concat(" ", ["modal-body", unwrapStr(i, className)]),
        },
        children,
      ),
  };
};

module Footer = {
  let component = ReasonReact.statelessComponent("Modal.Footer");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */ children,
      ) => {
    ...component,
    render: _self =>
      ReasonReact.createDomElement(
        tag,
        ~props={
          "className":
            String.concat(" ", ["modal-footer", unwrapStr(i, className)]),
        },
        children,
      ),
  };
};
