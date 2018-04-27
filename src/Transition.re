let optionMap = (fn, option) =>
  switch (option) {
  | Some(value) => Some(fn(value))
  | None => None
  };

module Transition = {
  [@bs.module "react-transition-group"]
  external transition : ReasonReact.reactClass = "Transition";
  let make =
      (
        ~_in: bool=false,
        ~mountOnEnter: bool=false,
        ~unmountOnExit: bool=false,
        ~appear: bool=false,
        ~enter: bool=true,
        ~exit: bool=true,
        ~timeout: option(int)=?,
        ~addEndListener: option((Dom.element, unit => unit) => unit)=?,
        ~onEnter: option((Dom.element, bool) => unit)=?,
        ~onEntering: option((Dom.element, bool) => unit)=?,
        ~onEntered: option((Dom.element, bool) => unit)=?,
        ~onExit: option(Dom.element => unit)=?,
        ~onExiting: option(Dom.element => unit)=?,
        ~onExited: option(Dom.element => unit)=?,
        ~className: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=transition,
      ~props={
        "in": _in,
        "mountOnEnter": mountOnEnter,
        "unmountOnExit": unmountOnExit,
        "appear": appear,
        "enter": enter,
        "exit": exit,
        "timeout": Js.Nullable.fromOption(timeout),
        "addEndListener": Js.Nullable.fromOption(addEndListener),
        "onEnter": Js.Nullable.fromOption(onEnter),
        "onEntering": Js.Nullable.fromOption(onEntering),
        "onEntered": Js.Nullable.fromOption(onEntered),
        "onExit": Js.Nullable.fromOption(onExit),
        "onExiting": Js.Nullable.fromOption(onExiting),
        "onExited": Js.Nullable.fromOption(onExited),
        "className": Js.Nullable.fromOption(className)
      },
      children
    );
};

module TransitionGroup = {
  [@bs.module "react-transition-group/TransitionGroup"]
  external transitionGroup : ReasonReact.reactClass = "default";
  let make =
      (
        ~component: string="div",
        ~appear: option(bool)=?,
        ~enter: option(bool)=?,
        ~exit: option(bool)=?,
        ~childFactory:
           option(ReasonReact.reactElement => ReasonReact.reactElement)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=transitionGroup,
      ~props={
        "component": component,
        "appear":
          Js.Nullable.fromOption(appear),
        "enter":
          Js.Nullable.fromOption(enter),
        "exit": Js.Nullable.fromOption(exit),
        "childFactory": Js.Nullable.fromOption(childFactory)
      },
      children
    );
};

module CSSTransition = {
  [@bs.module "react-transition-group"]
  external cssTransition : ReasonReact.reactClass = "CSSTransition";
  type classNames = {
    .
    "appear": Js.nullable(string),
    "appearActive": Js.nullable(string),
    "enter": Js.nullable(string),
    "enterActive": Js.nullable(string),
    "exit": Js.nullable(string),
    "exitActive": Js.nullable(string)
  };
  let classNames =
      (
        ~appear: option(string)=?,
        ~appearActive: option(string)=?,
        ~enter: option(string)=?,
        ~enterActive: option(string)=?,
        ~exit: option(string)=?,
        ~exitActive: option(string)=?,
        ()
      )
      : classNames => {
    "appear": Js.Nullable.fromOption(appear),
    "appearActive": Js.Nullable.fromOption(appearActive),
    "enter": Js.Nullable.fromOption(enter),
    "enterActive": Js.Nullable.fromOption(enterActive),
    "exit": Js.Nullable.fromOption(exit),
    "exitActive": Js.Nullable.fromOption(exitActive)
  };
  let make =
      (
        ~_in: bool=false,
        ~mountOnEnter: bool=false,
        ~unmountOnExit: bool=false,
        ~appear: bool=false,
        ~enter: bool=true,
        ~exit: bool=true,
        ~timeout: option(int)=?,
        ~addEndListener: option((Dom.element, unit => unit) => unit)=?,
        ~classNames: option(classNames)=?,
        ~onEnter: option((Dom.element, bool) => unit)=?,
        ~onEntering: option((Dom.element, bool) => unit)=?,
        ~onEntered: option((Dom.element, bool) => unit)=?,
        ~onExit: option(Dom.element => unit)=?,
        ~onExiting: option(Dom.element => unit)=?,
        ~onExited: option(Dom.element => unit)=?,
        ~className: option(string)=?,
        children
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=cssTransition,
      ~props={
        "in": _in,
        "mountOnEnter": mountOnEnter,
        "unmountOnExit": unmountOnExit,
        "appear": appear,
        "enter": enter,
        "exit": exit,
        "timeout": Js.Nullable.fromOption(timeout),
        "addEndListener": Js.Nullable.fromOption(addEndListener),
        "classNames": Js.Nullable.fromOption(classNames),
        "onEnter": Js.Nullable.fromOption(onEnter),
        "onEntering": Js.Nullable.fromOption(onEntering),
        "onEntered": Js.Nullable.fromOption(onEntered),
        "onExit": Js.Nullable.fromOption(onExit),
        "onExiting": Js.Nullable.fromOption(onExiting),
        "onExited": Js.Nullable.fromOption(onExited),
        "className": Js.Nullable.fromOption(className)
      },
      children
    );
};

module MyTransition = {
  type action =
    | Mounted;
  type status =
    | Unmounted
    | Exited
    | Entering
    | Entered
    | Exiting;
  type state = {
    status,
    nextStatus: status,
    timeoutId: option(Js.Global.timeoutId)
  };
  type retainedProps = {
    message: string,
    numbers: int,
    _in: bool
  };
  let component =
    ReasonReact.reducerComponentWithRetainedProps("MyTransition");
  let make =
      (~message: string, ~_in: bool, ~appear: bool, ~enter: bool, _children) => {
    ...component,
    initialState: () =>
      switch (_in, appear) {
      | (true, true) => {status: Exited, nextStatus: Entering, timeoutId: None}
      | (true, false) => {
          status: Entered,
          nextStatus: Exiting,
          timeoutId: None
        }
      | (false, _) => {status: Exited, nextStatus: Unmounted, timeoutId: None}
      },
    didUpdate: ({oldSelf, newSelf}) =>
      if (oldSelf.retainedProps.message !== newSelf.retainedProps.message) {
        Js.log("They are different");
      },
    /* Js.Global.setTimeout */
    retainedProps: ({message, numbers: 42, _in}: retainedProps),
    reducer: (action: action, _state) =>
      switch (action) {
      | Mounted =>
        ReasonReact.UpdateWithSideEffects(
          Entering,
          (_self => Js.log("Reducer called"))
        )
      },
    render: _self =>
      <div>
        <strong> (ReasonReact.string("Success")) </strong>
        <p> (ReasonReact.string(message)) </p>
      </div> /* self.reduce (fun () => Mounted), */ /* didMount: fun _self => ReasonReact.Update Entering, */
  };
};
