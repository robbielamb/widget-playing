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
  | Open
  | Close;

type state = {
  el: ref(option(Dom.element)),
  isBodyOverflowing: bool,
  isOpen: bool,
};

let initState = isOpen => {
  {el: ref(None), isBodyOverflowing: false, isOpen};
};

let addBackground = zIndex => {
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

  let _ =
    document
    |> Webapi.Dom.Document.asHtmlDocument
    |> andThen(Webapi.Dom.HtmlDocument.body)
    |> map(Webapi.Dom.Element.appendChild(el));
  el;
};

let removeBackground = el => {
  let document = Webapi.Dom.document;
  let _ =
    document
    |> Webapi.Dom.Document.asHtmlDocument
    |> andThen(Webapi.Dom.HtmlDocument.body)
    |> map(Webapi.Dom.Element.removeChild(el));
  ();
};

[@react.component]
let make =
    (
      ~isOpen: bool=false,
      ~onEnter: option(unit => unit)=?,
      ~zIndex: int=1050,
      ~children,
    ) => {
  let (state, dispatch) =
    React.useReducerWithMapState(
      (state, action) =>
        switch (action) {
        | Open => {...state, isOpen: true}
        | Close => {...state, isOpen: false}
        },
      isOpen,
      initState,
    );

  React.useEffect1(
    () => {
      switch (state.isOpen, isOpen) {
      | (true, false) =>
        switch(onEnter) {
          |None => ()
          | Some(cb) => cb()
        };
        dispatch(Close);
        switch (state.el^) {
        | Some(el) => removeBackground(el)
        | None => ()
        };
      | (false, true) =>
        dispatch(Open);
        let el = addBackground(zIndex);
        state.el := Some(el);
      | (_, _) => ()
      };
      None;
    },
    [|isOpen|],
  );

  !isOpen
    ? React.null
    : {
      let className =
        ["modal fade", isOpen ? "show" : ""] |> String.concat(" ");
      let style =
        ReactDOMRe.Style.make(~display=isOpen ? "block" : "none", ());

      let tabIndex = (-1);

      <div className role="dialog" tabIndex style>
        <div className="modal-dialog" role="document">
          <div className="modal-content"> children </div>
        </div>
      </div>;
    };
};

module Header = {
  [@react.component]
  let make =
      (
        ~toggle: option(ReactEvent.Mouse.t => unit)=?,
        ~className: option(string)=?,
        ~closeAriaLabel: string="Close",
        ~children,
      ) => {
    let className =
      ["modal-header", unwrapStr(i, className)] |> String.concat(" ");
    let closeButton =
      switch (toggle) {
      | None => React.null
      | Some(onClick) =>
        <button
          type_="button" onClick className="close" ariaLabel=closeAriaLabel>
          <span ariaHidden=true>
            {React.string(Js.String.fromCharCode(215))}
          </span>
        </button>
      };
    <div className>
      <h4 className="modal-title"> children </h4>
      closeButton
    </div>;
  };
};

module Body = {
  [@react.component]
  let make = (~className: option(string)=?, ~children) => {
    let className =
      String.concat(" ", ["modal-body", unwrapStr(i, className)]);
    <div className> children </div>;
  };
};

module Footer = {
  [@react.component]
  let make = (~className: option(string)=?, ~children) => {
    let className =
      String.concat(" ", ["modal-footer", unwrapStr(i, className)]);
    <div className> children </div>;
  };
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */;

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