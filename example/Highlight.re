[@bs.module "react-fast-highlight"]
external highlightClass: ReasonReact.reactClass = "default";

let make =
    (
      ~className: option(string)=?,
      ~languages: option(array(string))=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=highlightClass,
    ~props={
      "className": Js.Nullable.fromOption(className),
      "languages": Js.Nullable.fromOption(languages),
    },
    children,
  );
