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
      ~onEnter: option(unit => unit)=?,
      ~zIndex: int=1050,
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
  render: (_self: ReasonReact.self(state, retainedProps, actions)) =>
    !isOpen ?
      React.null :
      {
        let content =
          ReactDOMRe.createElementVariadic(
            "div",
            ~props={"className": "modal-content"}->ReactDOMRe.objToDOMProps,
            children,
          );
        let dialog =
          ReactDOMRe.createElement(
            "div",
            ~props=
              {"className": "modal-dialog", "role": "document"}
              ->ReactDOMRe.objToDOMProps,
            [|content|],
          );
        let classNames =
          ["modal fade", isOpen ? "show" : ""] |> String.concat(" ");
        let style =
          ReactDOMRe.Style.make(~display=isOpen ? "block" : "none", ());
        ReactDOMRe.createElement(
          "div",
          ~props=
            {
              "className": classNames,
              "role": "dialog",
              "style": style,
              "tabIndex": "-1",
            }
            ->ReactDOMRe.objToDOMProps,
          [|dialog|],
        );
      },
};

module Header = {
  let component = ReasonReact.statelessComponent("Modal.Header");
  let make =
      (
        ~tag: string="h4",
        ~wrapTag: string="div",
        ~toggle: option(ReactEvent.Mouse.t => unit)=?,
        ~className: option(string)=?,
        ~closeAriaLabel: string="Close",
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["modal-header", unwrapStr(i, className)] |> String.concat(" ");
      let closeButton =
        switch (toggle) {
        | None => React.null
        | Some(onClick) =>
          ReactDOMRe.createElement(
            "button",
            ~props=
              {
                "type": "button",
                "onClick": onClick,
                "className": "close",
                "aria-label": closeAriaLabel,
              }
              ->ReactDOMRe.objToDOMProps,
            [|
              ReactDOMRe.createElement(
                "span",
                ~props={"aria-hidden": "true"}->ReactDOMRe.objToDOMProps,
                [|React.string(Js.String.fromCharCode(215))|],
              ),
            |],
          )
        };
      let inner =
        ReactDOMRe.createElementVariadic(
          tag,
          ~props={"className": "modal-title"}->ReactDOMRe.objToDOMProps,
          children,
        );
      ReactDOMRe.createElementVariadic(
        wrapTag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        [|inner, closeButton|],
      );
    },
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "closeAriaLabel": option('closeAriaLabel),
          "className": option('className),
          "toggle": option('toggle),
          "wrapTag": option('wrapTag),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~closeAriaLabel=?reactProps##closeAriaLabel,
        ~className=?reactProps##className,
        ~toggle=?reactProps##toggle,
        ~wrapTag=?reactProps##wrapTag,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~tag: 'tag=?,
      ~wrapTag: 'wrapTag=?,
      ~toggle: 'toggle=?,
      ~className: 'className=?,
      ~closeAriaLabel: 'closeAriaLabel=?,
      unit
    ) =>
    {
      .
      "closeAriaLabel": option('closeAriaLabel),
      "className": option('className),
      "toggle": option('toggle),
      "wrapTag": option('wrapTag),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};

module Body = {
  let component = ReasonReact.statelessComponent("Modal.Body");
  let make = (~tag: string="div", ~className: option(string)=?, children) => {
    ...component,
    render: _self =>
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "className":
              String.concat(" ", ["modal-body", unwrapStr(i, className)]),
          }
          ->ReactDOMRe.objToDOMProps,
        children,
      ),
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
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
      ReactDOMRe.createElementVariadic(
        tag,
        ~props=
          {
            "className":
              String.concat(" ", ["modal-footer", unwrapStr(i, className)]),
          }
          ->ReactDOMRe.objToDOMProps,
        children,
      ),
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component,
      (
        reactProps: {
          .
          "className": option('className),
          "tag": option('tag),
          "children": 'children,
        },
      ) =>
      make(
        ~className=?reactProps##className,
        ~tag=?reactProps##tag,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, ~tag: 'tag=?, ~className: 'className=?, unit) =>
    {
      .
      "className": option('className),
      "tag": option('tag),
      "children": 'children,
    } =
    "";
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "zIndex": option('zIndex),
        "onEnter": option('onEnter),
        "isOpen": option('isOpen),
        "children": 'children,
      },
    ) =>
    make(
      ~zIndex=?reactProps##zIndex,
      ~onEnter=?reactProps##onEnter,
      ~isOpen=?reactProps##isOpen,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~isOpen: 'isOpen=?,
    ~onEnter: 'onEnter=?,
    ~zIndex: 'zIndex=?,
    unit
  ) =>
  {
    .
    "zIndex": option('zIndex),
    "onEnter": option('onEnter),
    "isOpen": option('isOpen),
    "children": 'children,
  } =
  "";

/*       ~autoFocus: bool=true,
         ~size: option(string)=?,
         ~toggle: option((ReactEvent.Mouse.t => unit))=?,
         ~keyboard: bool=true,
         ~role: string="dialog",
         ~labelledBy: option(string)=?,
         ~backdrop: bool=true, */

/*       ~onExit: option((unit => unit))=?,
         ~onOpened: option((unit => unit))=?,
         ~onClosed: option((unit => unit))=?,
         ~className: option(string)=?,
         ~wrapClassName: option(string)=?,
         ~modalClassName: option(string)=?,
         ~backdropClassName: option(string)=?,
         ~contentClassName: option(string)=?,
         ~fade: bool=true, */

/* backdropTransitionTimeout::(backdropTransitionTimeout: option int)=?
   backdropTransitionAppearTimeout::(backdropTransitionAppearTimeout: option int)=?
   backdropTransitionEnterTimeout::(backdropTransitionEnterTimeout: option int)=?
   backdropTransitionLeaveTimeout::(backdropTransitionLeaveTimeout: option int)=?
   modalTransitionTimeout::(modalTransitionTimeout: option int)=?
   modalTransitionAppearTimeout::(modalTransitionAppearTimeout: option int)=?
   modalTransitionEnterTimeout::(modalTransitionEnterTimeout: option int)=?
   modalTransitionLeaveTimeout::(modalTransitionLeaveTimeout: option int)=? */

/*|> unwrapUnsafely*/

/* Webapi.Dom.CssStyleDeclaration.t; */
/* Webapi; */
/* willReceiveProps: fun self => self.state, */
/* shouldUpdate: fun {oldSelf, newSelf} => (oldSelf.retainedProps.isOpen === newSelf.retainedProps.isOpen) ? true : false, */

/* willUpdate: fun _oldAndNewSelf => (), */

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */
