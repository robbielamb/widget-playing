include Utils;

include ColorsRe;

type action =
  | Open
  | Closing
  | Closed;

type state = {
  currentAction: action,
  timer: ref(option(Js.Global.timeoutId)),
};

type retainedProps = {isOpen: bool};

let component = ReasonReact.reducerComponentWithRetainedProps("Alert");

let make =
    (
      ~className: option(string)=?,
      ~closeClassName: option(string)=?,
      ~color: Color.t=Color.Success,
      ~isOpen: bool=true,
      ~toggle: option(ReactEvent.Mouse.t => unit)=?,
      ~closeAriaLabel: string="Close",
      ~onClosed: option(unit => unit)=?,
      children,
    ) => {
  ...component,
  initialState: () => {
    currentAction: isOpen ? Open : Closed,
    timer: ref(None),
  },
  retainedProps: ({isOpen: isOpen}: retainedProps),
  didMount: _self => (),
  willReceiveProps: self =>
    if (self.state.currentAction === Open && isOpen === false) {
      let timer = Js.Global.setTimeout(_ => self.send(Closed), 250);
      {currentAction: Closing, timer: ref(Some(timer))};
    } else {
      self.state;
    },
  willUnmount: self => {
    self.state.timer := None;
    ();
  },
  reducer: (action, state) =>
    switch (action) {
    | Open => ReasonReact.Update({...state, currentAction: Open})
    | Closing => ReasonReact.Update({...state, currentAction: Closing})
    | Closed =>
      ReasonReact.UpdateWithSideEffects(
        {...state, currentAction: Closed},
        (
          _self =>
            switch (onClosed) {
            | None => ()
            | Some(cb) => cb()
            }
        ),
      )
    },
  render: (self: ReasonReact.self(state, retainedProps, action)) => {
    let closeClasses =
      ["close", unwrapStr(i, closeClassName)] |> String.concat(" ");
    let toggleElement =
      switch (toggle) {
      | None => React.null
      | Some(cb) =>
        ReactDOMRe.createElement(
          "button",
          ~props=
            {
              "type": "button",
              "className": closeClasses,
              "onClick": cb,
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
    let children = ArrayLabels.append([|toggleElement|], children);
    let transitionClasses =
      switch (self.state.currentAction) {
      | Open => "fade show"
      | Closing => "fade"
      | Closed => ""
      };
    let classes =
      [
        "alert",
        "alert-" ++ Color.toString(color),
        transitionClasses,
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
     
    let alertElement = <div className=classes> (React.string("Im alert")) </div>;
      
    self.state.currentAction === Closed ? React.null : alertElement;
  },
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
        ~closeAriaLabel: string="Close",
        ~onClosed: option(unit => unit)=?,
        children,
      ) => {
    ...component,
    initialState: () => true,
    reducer: (action, _state) =>
      switch (action) {
      | DoClose => ReasonReact.Update(false)
      },
    render: self =>
      ReasonReact.element(
        make(
          ~className?,
          ~color,
      
          ~closeAriaLabel,
          ~isOpen=self.state,
          ~toggle=_ => self.send(DoClose),
          ~onClosed?,
          children,
        ),
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
          "onClosed": option('onClosed),
          "closeAriaLabel": option('closeAriaLabel),
         
          "color": option('color),
          "className": option('className),
          "children": 'children,
        },
      ) =>
      make(
        ~onClosed=?reactProps##onClosed,
        ~closeAriaLabel=?reactProps##closeAriaLabel,
       
        ~color=?reactProps##color,
        ~className=?reactProps##className,
        reactProps##children,
      )
    );
  [@bs.obj]
  external makeProps:
    (
      ~children: 'children,
      ~className: 'className=?,
      ~color: 'color=?,
      ~tag: 'tag=?,
      ~closeAriaLabel: 'closeAriaLabel=?,
      ~onClosed: 'onClosed=?,
      unit
    ) =>
    {
      .
      "onClosed": option('onClosed),
      "closeAriaLabel": option('closeAriaLabel),
      "tag": option('tag),
      "color": option('color),
      "className": option('className),
      "children": 'children,
    } =
    "";
};

module Link = {
  let component = ReasonReact.statelessComponent("Alert.Link");
  let make = children => {
    ...component,
    render: _self =>
      ReactDOMRe.createElementVariadic(
        "a",
        ~props={"className": "alert-link"}->ReactDOMRe.objToDOMProps,
        children,
      ),
  };
  /**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
  let make =
    ReasonReactCompat.wrapReasonReactForReact(
      ~component, (reactProps: {. "children": 'children}) =>
      make(reactProps##children)
    );
  [@bs.obj]
  external makeProps:
    (~children: 'children, unit) => {. "children": 'children} =
    "";
};

module Heading = {
  let component = ReasonReact.statelessComponent("Alert.Header");
  let make = (~tag: string="h4", ~className: option(string)=?, children) => {
    ...component,
    render: _self => {
      let classes =
        ["alert-heading", unwrapStr(i, className)] |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}->ReactDOMRe.objToDOMProps,
        children,
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
        "onClosed": option('onClosed),
        "closeAriaLabel": option('closeAriaLabel),
        "toggle": option('toggle),
        "isOpen": option('isOpen),
        "color": option('color),
        "closeClassName": option('closeClassName),
        "className": option('className),
        "children": 'children,
      },
    ) =>
    make(
      ~onClosed=?reactProps##onClosed,
      ~closeAriaLabel=?reactProps##closeAriaLabel,
      ~toggle=?reactProps##toggle,
      ~isOpen=?reactProps##isOpen,
      ~color=?reactProps##color,
      ~closeClassName=?reactProps##closeClassName,
      ~className=?reactProps##className,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~className: 'className=?,
    ~closeClassName: 'closeClassName=?,
    ~color: 'color=?,
    ~isOpen: 'isOpen=?,
    ~toggle: 'toggle=?,
    ~closeAriaLabel: 'closeAriaLabel=?,
    ~onClosed: 'onClosed=?,
    unit
  ) =>
  {
    .
    "onClosed": option('onClosed),
    "closeAriaLabel": option('closeAriaLabel),
    "toggle": option('toggle),
    "isOpen": option('isOpen),
    "color": option('color),
    "closeClassName": option('closeClassName),
    "className": option('className),
    "children": 'children,
  } =
  "";

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */

/*  ::?cssModule */

/* TODO: Add more link */
