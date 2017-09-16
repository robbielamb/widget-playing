type jsUnsafe;

external toJsUnsafe : 'a => jsUnsafe = "%identity";

let unwrapValue =
  fun
  | `String s => toJsUnsafe s
  | `Bool b => toJsUnsafe (Js.Boolean.to_js_boolean b)
  | `Float f => toJsUnsafe f
  | `Date d => toJsUnsafe d
  | `Callback c => toJsUnsafe c
  | `Element e => toJsUnsafe e
  | `Object o => toJsUnsafe o
  | `Enum _ => assert false;

let optionMap fn option =>
  switch option {
  | Some value => Some (fn value)
  | None => None
  };


module Badge = BadgeRe;

module BreadCrumb = BreadcrumbRe;

module Button = ButtonRe;

/* module Collapse = {
     external collapse : ReasonReact.reactClass = "Collapse" [@@bs.module "reactstrap"];
     type delayShape = Js.t {. show : int, hide : int};
     type delayProps = option [ | `Float float | `Object delayShape];
     let make
         isOpen::(isOpen: bool)=false
         tag::(tag: option [ | `String string | `Element ReasonReact.reactElement])=?
         className::(className: option string)=?
         cssModule::(cssModule: option (Js.t {..}))=?
         navbar::(navbar: bool)=false
         delay::(delay: delayProps)=?
         onOpen::(onOpen: option (unit => unit))=?
         onClosed::(onClosed: option (unit => unit))=?
         children =>
       ReasonReact.wrapJsForReason
         props::{
           "isOpen": Js.Boolean.to_js_boolean isOpen,
           "tag": Js.Null_undefined.from_opt (optionMap unwrapValue tag),
           "className": Js.Null_undefined.from_opt className,
           "cssModule": Js.Null_undefined.from_opt cssModule,
           "navbar": Js.Boolean.to_js_boolean navbar,
           "delay": Js.Null_undefined.from_opt (optionMap unwrapValue delay),
           "onOpen": Js.Null_undefined.from_opt onOpen,
           "onClosed": Js.Null_undefined.from_opt onClosed
         }
         children;
   }; */
module DropDownToggle = {};

module DropdownMenu = {};

module DropdownItem = {};

module Fade = {
  /*   let component = ReasonReact.statelessComponent "Fade";

       let make _in::(_in: bool)=false timeout::(timeout: int)=300 mountOnEnter::(mountOnEnter: bool)=false mountOnExit::(mountOnExit: bool)=false children => {
         Transition.Transition.make enteredClassName="in" children;
       }; */
};

module Alert = AlertRe;

module Card = CardRe;

module Form = FormRe;

module Layout = LayoutRe;

module Nav = NavRe;

module Navbar = NavbarRe;

module Modal = ModalRe;
module Progress = ProgressRe;