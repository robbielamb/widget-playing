include Utils;

include ColorsRe;

type action =
  | Open
  | Closing
  | Closed;

type state = {currentAction: action};

type retainedProps = {isOpen: bool};

let unsetTimer = timer =>
  switch (timer) {
  | None => ()
  | Some(id) => Js.Global.clearTimeout(id)
  };

let initialState = isOpen => {
  {currentAction: isOpen ? Open : Closed};
};

let reducer = (_state, action): state => {
  switch (action) {
  | Open => {currentAction: Open}
  | Closing => {currentAction: Closing}
  | Closed => {currentAction: Closed}
  };
};

[@react.component]
let make =
    (
      ~className: option(string)=?,
      ~closeClassName: option(string)=?,
      ~color: Color.t=Color.Success,
      ~isOpen: bool=true,
      ~toggle: option(ReactEvent.Mouse.t => unit)=?,
      ~closeAriaLabel: string="Close",
      ~onClosed: option(unit => unit)=?,
      ~children,
    ) => {
  let (state, dispatch) =
    React.useReducerWithMapState(reducer, isOpen, initialState);

  React.useEffect1(
    () => {
      let timer =
        if (state.currentAction == Open && isOpen === false) {
          dispatch(Closing);
          let timer = Js.Global.setTimeout(_ => dispatch(Closed), 150);
          Some(timer);
        } else {
          None;
        };
      Some(() => unsetTimer(timer));
    },
    [|isOpen|],
  );

  React.useEffect1(
    () => {
      switch (state.currentAction) {
      | Closed =>
        switch (onClosed) {
        | None => ()
        | Some(cb) => cb()
        }
      | _ => ()
      };
      None;
    },
    [|state.currentAction|],
  );

  let closeClasses =
    ["close", unwrapStr(i, closeClassName)] |> String.concat(" ");
  let toggleElement =
    switch (toggle) {
    | None => React.null
    | Some(cb) =>
      <button
        type_="button"
        className=closeClasses
        onClick=cb
        ariaLabel=closeAriaLabel>
        <span ariaHidden=true>
          {React.string(Js.String.fromCharCode(215))}
        </span>
      </button>
    };

  let transitionClasses =
    switch (state.currentAction) {
    | Open => "fade show"
    | Closing => "fade"
    | Closed => ""
    };
  let className =
    [
      "alert",
      "alert-" ++ Color.toString(color),
      transitionClasses,
      unwrapStr(i, className),
    ]
    |> String.concat(" ");

  let alertElement = <div className> toggleElement children </div>;

  state.currentAction === Closed ? React.null : alertElement;
};

module Auto = {
  [@react.component]
  let makeAuto =
      (
        ~className: option(string)=?,
        ~color: Color.t=Color.Success,
        ~closeAriaLabel: string="Close",
        ~onClosed: option(unit => unit)=?,
        ~children,
      ) => {
    let (isOpen, setOpen) = React.useState(() => true);

    let theProps =
      makeProps(
        ~className?,
        ~color,
        ~closeAriaLabel,
        ~onClosed?,
        ~isOpen,
        ~toggle=_evt => setOpen(_ => !isOpen),
        ~children,
        (),
      );

    make(theProps);
    //<Alert ?className color closeAriaLabel ?onClosed toggle=(_) => setOpen(false)> children </Alert>
  };

  let makeProps = makeAutoProps;
  let make = makeAuto;
};

module Link = {
  [@react.component]
  let make = (~children) => {
    <a className="alert-link"> children </a>;
  };
};

module Heading = {
  [@react.component]
  let make = (~className: option(string)=?, ~children) => {
    let className =
      ["alert-heading", unwrapStr(i, className)] |> String.concat(" ");
    <h4 className> children </h4>;
  };
};

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */

/*  ::?cssModule */

/* TODO: Add more link */