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

module Alert = AlertRe;

module Badge = BadgeRe;

module BreadCrumb = BreadcrumbRe;

module Button = ButtonRe;

module Dropdown = DropdownRe;

module Fade = {
  /*   let component = ReasonReact.statelessComponent "Fade";

       let make _in::(_in: bool)=false timeout::(timeout: int)=300 mountOnEnter::(mountOnEnter: bool)=false mountOnExit::(mountOnExit: bool)=false children => {
         Transition.Transition.make enteredClassName="in" children;
       }; */
};

module Card = CardRe;

module Collapse = CollapseRe;

module Form = FormRe;

module Input = InputRe;

module Jumbotron = JumbotronRe;

module Layout = LayoutRe;

module Nav = NavRe;

module Navbar = NavbarRe;

module Modal = ModalRe;

module Pagination = PaginationRe;

module Progress = ProgressRe;

module Table = TableRe;