include Utils;
include ColorsRe;

type action =
  | Open
  | Closing
  | Closed;

type state = {
  currentAction: action,
  timer: ref(option(Js.Global.timeoutId))
};

type retainedProps = {isOpen: bool};

let component = ReasonReact.reducerComponentWithRetainedProps("Alert");

let make =
    (
      ~className: option(string)=?,
      ~closeClassName: option(string)=?,
      ~color: Color.t=Color.Success,
      ~isOpen: bool=true,
      ~toggle: option((ReactEventRe.Mouse.t => unit))=?,
      ~tag: string="div",
      ~closeAriaLabel: string="Close",
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children
    ) => {
  ...component,
  initialState: () => {currentAction: isOpen ? Open : Closed, timer: ref(None)},
  retainedProps: ({isOpen: isOpen}: retainedProps),
  didMount: (_self) => ReasonReact.NoUpdate,
  willReceiveProps: (self) =>
    if (self.state.currentAction === Open && isOpen === false) {
      let timer = Js.Global.setTimeout(self.reduce((_) => Closed), 250);
      {currentAction: Closing, timer: ref(Some(timer))}
    } else {
      self.state
    },
  willUnmount: (self) => {
    self.state.timer := None;
    ()
  },
  reducer: (action, state) =>
    switch action {
    | Open => ReasonReact.Update({...state, currentAction: Open})
    | Closing => ReasonReact.Update({...state, currentAction: Closing})
    | Closed => ReasonReact.Update({...state, currentAction: Closed})
    },
  render: (self: ReasonReact.self(state, retainedProps, action)) => {
    let closeClasses = ["close", unwrapStr(i, closeClassName)] |> String.concat(" ");
    let toggleElement =
      switch toggle {
      | None => ReasonReact.nullElement
      | Some(cb) =>
        ReasonReact.createDomElement(
          "button",
          ~props={
            "type": "button",
            "className": closeClasses,
            "onClick": cb,
            "aria-label": closeAriaLabel
          },
          [|
            ReasonReact.createDomElement(
              "span",
              ~props={"aria-hidden": "true"},
              [|ReasonReact.stringToElement(Js.String.fromCharCode(215))|]
            )
          |]
        )
      };
    let children = ArrayLabels.append([|toggleElement|], children);
    let transitionClasses =
      switch self.state.currentAction {
      | Open => "fade show"
      | Closing => "fade"
      | Closed => ""
      };
    let classes =
      [
        "alert",
        "alert" ++ Color.toString(color),
        transitionClasses,
        unwrapStr(i, className)
      ]
      |> String.concat(" ");
    let alertElement = ReasonReact.createDomElement(tag, ~props={"className": classes}, children);
    self.state.currentAction === Closed ? ReasonReact.nullElement : alertElement
  }
};

module Auto = {
  type state = bool;
  type action =
    | DoClose;
  let component = ReasonReact.reducerComponent("Alert.Auto");
  let make =
      (
        ~className: option(string)=?,
        ~color: Color.t=Color.Success,
        ~tag: string="div",
        ~closeAriaLabel: string="Close",
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        children
      ) => {
    ...component,
    initialState: () => true,
    reducer: (action, _state) =>
      switch action {
      | DoClose => ReasonReact.Update(false)
      },
    render: (self) =>
      ReasonReact.element(
        make(
          ~className?,
          ~color,
          ~tag,
          ~closeAriaLabel,
          /*  ::?cssModule */
          ~isOpen=self.state,
          ~toggle=self.reduce((_) => DoClose),
          children
        )
      )
  };
};

module Link = {
  /* TODO: Add more link */
  let component = ReasonReact.statelessComponent("Alert.Link");
  let make = (children) => {
    ...component,
    render: (_self) =>
      ReasonReact.createDomElement("a", ~props={"className": "alert-link"}, children)
  };
};

module Heading = {
  let component = ReasonReact.statelessComponent("Alert.Header");
  let make = (~tag: string="h4", ~className: option(string)=?, children) => {
    ...component,
    render: (_self) => {
      let classes = ["alert-heading", unwrapStr(i, className)] |> String.concat(" ");
      ReasonReact.createDomElement(tag, ~props={"className": classes}, children)
    }
  };
};