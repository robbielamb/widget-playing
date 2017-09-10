let optionMap fn option =>
  switch option {
  | Some value => Some (fn value)
  | None => None
  };

module Transition = {
  external transition : ReasonReact.reactClass =
    "default" [@@bs.module "react-transition-group/Transition"];
  let make
      _in::(_in: bool)=false
      mountOnEnter::(mountOnEnter: bool)=false
      mountOnExit::(mountOnExit: bool)=false
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
        "mountOnExit": Js.Boolean.to_js_boolean mountOnExit,
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
    "default" [@@bs.module "react-transition/TransitionGroup"];
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
    "default" [@@bs.module "react-transition-group/CSSTransition"];
  let make
      _in::(_in: bool)=false
      mountOnEnter::(mountOnEnter: bool)=false
      mountOnExit::(mountOnExit: bool)=false
      appear::(appear: bool)=false
      enter::(enter: bool)=true
      exit::(exit: bool)=true
      timeout::(timeout: option int)=?
      addEndListener::(addEndListener: option (Dom.element => (unit => unit) => unit))=?
      classNames::(classNames: option string)=?
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
        "mountOnExit": Js.Boolean.to_js_boolean mountOnExit,
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