[@bs.module "react-fast-highlight"] external highlightClass : ReasonReact.reactClass = "default";

let make = (~className: option(string)=?, ~languages: option(array(string))=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=highlightClass,
    ~props={
      "className": Js.Null_undefined.from_opt(className),
      "languages": Js.Null_undefined.from_opt(languages)
    },
    children
  );
