include Utils;

type action =
  | Opened
  | StartClosing
  | Closing
  | StartOpening
  | Opening
  | Closed;

type state = {
  isOpen: bool,
  currentState: action,
  timer: ref(option(Js.Global.timeoutId)),
  element: ReactDOMRe.domRef,
  height: option(string),
};

let actionToStr = action => {
  switch (action) {
  | Opened => "Opened"
  | StartClosing => "StartClosing"
  | Closing => "Closing"
  | StartOpening => "StartOpening"
  | Opening => "Opening"
  | Closed => "Closed"
  };
};

let maybeCall = mb =>
  switch (mb) {
  | None => ()
  | Some(cb) => cb()
  };

let unsetTimer = timer =>
  switch (timer) {
  | None => ()
  | Some(id) => Js.Global.clearTimeout(id)
  };

let getHeight = (maybeElement: ReactDOMRe.domRef) => {
  switch (Utils.optionDomRef(maybeElement)) {
  | None => ""
  | Some(el) => ReactDOMRe.domElementToObj(el)##scrollHeight ++ "px"
  };
};
let initialState = isOpen => {
  isOpen,
  currentState: isOpen ? Opened : Closed,
  timer: ref(None),
  element: Utils.createRef(),
  height: None,
};

let setTimer = (send, action, timeout) =>
  Some(Js.Global.setTimeout(_ => send(action), timeout));

let reducer = (state, action): state => {
  switch (action) {
  | Opened => {...state, currentState: Opened, height: None}
  | Closed => {...state, currentState: Closed, height: None}

  | StartClosing => {
      ...state,
      height: Some(getHeight(state.element)),
      currentState: StartClosing,
    }
  | Closing => {
      ...state,
      height: Some("0px"),
      currentState: Closing,
      isOpen: false,
    }

  | StartOpening => {...state, currentState: StartOpening}
  | Opening => {
      ...state,
      height: Some(getHeight(state.element)),
      currentState: Opening,
      isOpen: true,
    }
  };
};

[@react.component]
let make =
    (
      ~isOpen: bool=true,
      ~onOpening: option(unit => unit)=?,
      ~onOpened: option(unit => unit)=?,
      ~onClosing: option(unit => unit)=?,
      ~onClosed: option(unit => unit)=?,
      ~className: option(string)=?,
      ~children,
    ) => {
  let (state, dispatch) =
    React.useReducerWithMapState(reducer, isOpen, initialState);

  React.useEffect1(
    () => {
      if (state.isOpen !== isOpen) {
        let _ = unsetTimer(state.timer^);
        switch (state.currentState) {
        | Opened
        | StartOpening
        | Opening => dispatch(StartClosing)
        | Closed
        | StartClosing
        | Closing => dispatch(StartOpening)
        };
      };
      Some(
        () => {
          unsetTimer(state.timer^);
          state.timer := None;
        },
      );
    },
    [|isOpen|],
  );

  React.useEffect1(
    () => {
      switch (state.currentState) {
      | Opened => maybeCall(onOpened)
      | Closed => maybeCall(onClosed)
      | StartClosing => state.timer := setTimer(dispatch, Closing, 16) // Magic Number?
      | Closing =>
        maybeCall(onClosing);
        state.timer := setTimer(dispatch, Closed, 350);
      | StartOpening => dispatch(Opening)
      | Opening =>
        maybeCall(onOpening);
        state.timer := setTimer(dispatch, Opened, 350);
      };
      None;
    },
    [|state.currentState|],
  );

  let collapsingClasses =
    switch (state.currentState) {
    | Opened => "collapse show"
    | Closed => "collapse"
    | _ => "collapsing"
    };
  let className =
    [collapsingClasses, unwrapStr(i, className)] |> String.concat(" ");

  let style = ReactDOMRe.Style.make(~height=?state.height, ());
  <div className ref={state.element} style> children </div>;
};

/* state.height := getHeight !state.element */