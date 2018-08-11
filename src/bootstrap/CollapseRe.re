include Utils;

type action =
  | Opened
  | StartClosing
  | Closing
  | StartOpening
  | Opening
  | Closed;

type state = {
  currentState: action,
  timer: ref(option(Js.Global.timeoutId)),
  element: ref(option(ReasonReact.reactRef)),
  height: ref(option(string)),
};

type retainedProps = {isOpen: bool};

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

let getHeight = maybeElement =>
  switch (maybeElement) {
  | None => ""
  | Some(el) => ReasonReact.refToJsObj(el)##scrollHeight ++ "px"
  };

let setRef = (theRef, state) =>
  state.element := Js.Nullable.toOption(theRef);

/* state.height := getHeight !state.element */
let component = ReasonReact.reducerComponentWithRetainedProps("Collapse");

let make =
    (
      ~isOpen: bool=true,
      ~onOpening: option(unit => unit)=?,
      ~onOpened: option(unit => unit)=?,
      ~onClosing: option(unit => unit)=?,
      ~onClosed: option(unit => unit)=?,
      ~tag: string="div",
      ~className: option(string)=?,
      children,
    ) => {
  ...component,
  initialState: () => {
    currentState: isOpen ? Opened : Closed,
    timer: ref(None),
    element: ref(None),
    height: ref(None),
  },
  retainedProps: {
    isOpen: isOpen,
  },
  willReceiveProps: self => {
    let setTimer = action =>
      Some(Js.Global.setTimeout(_ => self.send(action), 0));
    if (self.retainedProps.isOpen !== isOpen) {
      let _ = unsetTimer(self.state.timer^);
      switch (self.state.currentState) {
      | Opened
      | StartOpening
      | Opening => {
          ...self.state,
          currentState: StartClosing,
          timer: ref(setTimer(StartClosing)),
          height: ref(Some(getHeight(self.state.element^))),
        }
      | Closed
      | StartClosing
      | Closing => {
          ...self.state,
          currentState: StartOpening,
          timer: ref(setTimer(StartOpening)),
          height: ref(None),
        }
      };
    } else {
      self.state;
    };
  },
  willUnmount: self => {
    unsetTimer(self.state.timer^);
    self.state.timer := None;
    ();
  },
  reducer: (action, state) => {
    let setTimer = (send, action, timeout) =>
      Some(Js.Global.setTimeout(_ => send(action), timeout));
    switch (action) {
    | Opened =>
      ReasonReact.UpdateWithSideEffects(
        {...state, currentState: Opened, height: ref(None)},
        (_self => maybeCall(onOpened)),
      )
    | Closed =>
      ReasonReact.UpdateWithSideEffects(
        {...state, currentState: Closed, height: ref(None)},
        (_self => maybeCall(onClosed)),
      )
    | StartClosing =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          height: ref(Some(getHeight(state.element^))),
          currentState: Closing,
        },
        (({send}) => send(Closing)),
      )
    | Closing =>
      ReasonReact.UpdateWithSideEffects(
        {...state, height: ref(Some("0"))},
        (
          ({state, send}) => {
            maybeCall(onClosing);
            state.timer := setTimer(send, Closed, 350);
          }
        ),
      )
    | StartOpening =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          height: ref(Some(getHeight(state.element^))),
          currentState: Opening,
        },
        (({send}) => send(Opening)),
      )
    | Opening =>
      ReasonReact.SideEffects(
        (
          ({send}) => {
            maybeCall(onOpening);
            state.timer := setTimer(send, Opened, 350);
          }
        ),
      )
    };
  },
  render: (self: ReasonReact.self(state, retainedProps, action)) => {
    let collapsingClasses =
      switch (self.state.currentState) {
      | Opened => "collapse show"
      | Closed => "collapse"
      | _ => "collapsing"
      };
    let classes =
      [collapsingClasses, unwrapStr(i, className)] |> String.concat(" ");
    let maybeHeight = self.state.height^;
    let style = ReactDOMRe.Style.make(~height=?maybeHeight, ());
    ReasonReact.createDomElement(
      tag,
      ~props={
        "className": classes,
        "ref": reactRef => setRef(reactRef, self.state),
        "style": style,
      },
      children,
    );
  },
};
