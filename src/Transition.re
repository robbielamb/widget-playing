let optionMap fn option =>
  switch option {
  | Some value => Some (fn value)
  | None => None
  };

module Transition = {
  external transition : ReasonReact.reactClass =
    "Transition" [@@bs.module "react-transition-group"];
  let make
      _in::(_in: bool)=false
      mountOnEnter::(mountOnEnter: bool)=false
      unmountOnExit::(unmountOnExit: bool)=false
      appear::(appear: bool)=false
      enter::(enter: bool)=true
      exit::(exit: bool)=true
      timeout::(timeout: option int)=?
      addEndListener::(addEndListener: option (Dom.element => (unit => unit) => unit))=?
      onEnter::(onEnter: option (Dom.element => bool => unit))=?
      onEntering::(onEntering: option (Dom.element => bool => unit))=?
      onEntered::(onEntered: option (Dom.element => bool => unit))=?
      onExit::(onExit: option (Dom.element => unit))=?
      onExiting::(onExiting: option (Dom.element => unit))=?
      onExited::(onExited: option (Dom.element => unit))=?
      className::(className: option string)=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::transition
      props::{
        "in": Js.Boolean.to_js_boolean _in,
        "mountOnEnter": Js.Boolean.to_js_boolean mountOnEnter,
        "unmountOnExit": Js.Boolean.to_js_boolean unmountOnExit,
        "appear": Js.Boolean.to_js_boolean appear,
        "enter": Js.Boolean.to_js_boolean enter,
        "exit": Js.Boolean.to_js_boolean exit,
        "timeout": Js.Null_undefined.from_opt timeout,
        "addEndListener": Js.Null_undefined.from_opt addEndListener,
        "onEnter": Js.Null_undefined.from_opt onEnter,
        "onEntering": Js.Null_undefined.from_opt onEntering,
        "onEntered": Js.Null_undefined.from_opt onEntered,
        "onExit": Js.Null_undefined.from_opt onExit,
        "onExiting": Js.Null_undefined.from_opt onExiting,
        "onExited": Js.Null_undefined.from_opt onExited,
        "className": Js.Null_undefined.from_opt className
      }
      children;
};

module TransitionGroup = {
  external transitionGroup : ReasonReact.reactClass =
    "default" [@@bs.module "react-transition-group/TransitionGroup"];
  let make
      component::(component: string)="div"
      appear::(appear: option bool)=?
      enter::(enter: option bool)=?
      exit::(exit: option bool)=?
      childFactory::(childFactory: option (ReasonReact.reactElement => ReasonReact.reactElement))=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::transitionGroup
      props::{
        "component": component,
        "appear": Js.Undefined.from_opt (optionMap Js.Boolean.to_js_boolean appear),
        "enter": Js.Undefined.from_opt (optionMap Js.Boolean.to_js_boolean enter),
        "exit": Js.Undefined.from_opt (optionMap Js.Boolean.to_js_boolean exit),
        "childFactory": Js.Undefined.from_opt childFactory
      }
      children;
};

module CSSTransition = {
  external cssTransition : ReasonReact.reactClass =
    "CSSTransition" [@@bs.module "react-transition-group"];
  type classNames =
    Js.t {
      .
      appear : Js.null_undefined string,
      appearActive : Js.null_undefined string,
      enter : Js.null_undefined string,
      enterActive : Js.null_undefined string,
      exit : Js.null_undefined string,
      exitActive : Js.null_undefined string
    };
  let classNames
      appear::(appear: option string)=?
      appearActive::(appearActive: option string)=?
      enter::(enter: option string)=?
      enterActive::(enterActive: option string)=?
      exit::(exit: option string)=?
      exitActive::(exitActive: option string)=?
      ()
      :classNames => {
    "appear": Js.Null_undefined.from_opt appear,
    "appearActive": Js.Null_undefined.from_opt appearActive,
    "enter": Js.Null_undefined.from_opt enter,
    "enterActive": Js.Null_undefined.from_opt enterActive,
    "exit": Js.Null_undefined.from_opt exit,
    "exitActive": Js.Null_undefined.from_opt exitActive
  };
  let make
      _in::(_in: bool)=false
      mountOnEnter::(mountOnEnter: bool)=false
      unmountOnExit::(unmountOnExit: bool)=false
      appear::(appear: bool)=false
      enter::(enter: bool)=true
      exit::(exit: bool)=true
      timeout::(timeout: option int)=?
      addEndListener::(addEndListener: option (Dom.element => (unit => unit) => unit))=?
      classNames::(classNames: option classNames)=?
      onEnter::(onEnter: option (Dom.element => bool => unit))=?
      onEntering::(onEntering: option (Dom.element => bool => unit))=?
      onEntered::(onEntered: option (Dom.element => bool => unit))=?
      onExit::(onExit: option (Dom.element => unit))=?
      onExiting::(onExiting: option (Dom.element => unit))=?
      onExited::(onExited: option (Dom.element => unit))=?
      className::(className: option string)=?
      children =>
    ReasonReact.wrapJsForReason
      reactClass::cssTransition
      props::{
        "in": Js.Boolean.to_js_boolean _in,
        "mountOnEnter": Js.Boolean.to_js_boolean mountOnEnter,
        "unmountOnExit": Js.Boolean.to_js_boolean unmountOnExit,
        "appear": Js.Boolean.to_js_boolean appear,
        "enter": Js.Boolean.to_js_boolean enter,
        "exit": Js.Boolean.to_js_boolean exit,
        "timeout": Js.Null_undefined.from_opt timeout,
        "addEndListener": Js.Null_undefined.from_opt addEndListener,
        "classNames": Js.Null_undefined.from_opt classNames,
        "onEnter": Js.Null_undefined.from_opt onEnter,
        "onEntering": Js.Null_undefined.from_opt onEntering,
        "onEntered": Js.Null_undefined.from_opt onEntered,
        "onExit": Js.Null_undefined.from_opt onExit,
        "onExiting": Js.Null_undefined.from_opt onExiting,
        "onExited": Js.Null_undefined.from_opt onExited,
        "className": Js.Null_undefined.from_opt className
      }
      children;
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
    timeoutId: option Js.Global.timeoutId
  };
  type retainedProps = {
    message: string,
    numbers: int,
    _in: bool
  };
  let component = ReasonReact.reducerComponentWithRetainedProps "MyTransition";
  let make
      message::(message: string)
      _in::(_in: bool)
      appear::(appear: bool)
      enter::(enter: bool)
      _children => {
    ...component,
    initialState: fun () => switch (_in, appear) {
    | (true,true) => {status: Exited, nextStatus: Entering, timeoutId: None}
    | (true, false) => {status: Entered, nextStatus: Exiting, timeoutId: None}
    | (false, _) => { status: Exited, nextStatus: Unmounted, timeoutId: None}
    },
    didUpdate: fun {oldSelf, newSelf} =>
      if (oldSelf.retainedProps.message !== newSelf.retainedProps.message) {
        Js.log "They are different";
        
        /* Js.Global.setTimeout */
      },
    retainedProps: ({message, numbers: 42, _in}: retainedProps), /* self.reduce (fun () => Mounted), */ /* didMount: fun _self => ReasonReact.Update Entering, */
    reducer: fun (action: action) _state =>
      switch action {
      | Mounted =>
        ReasonReact.UpdateWithSideEffects Entering (fun _self => Js.log "Reducer called")
      },
    render: fun _self =>
      <div>
        <strong> (ReasonReact.stringToElement "Success") </strong>
        <p> (ReasonReact.stringToElement message) </p>
      </div>
  };
};