include Utils;

let component = ReasonReact.statelessComponent("BreadCrumb");

let make =
    (
      ~tag: string="ol",
      ~className: option(string)=?,
      /* cssModule::(cssModule: option (Js.t {..}))=? */
      children,
    ) => {
  ...component,
  render: _self => {
    let classes =
      ["breadcrumb", unwrapStr(i, className)] |> String.concat(" ");
    ReactDOMRe.createElementVariadic(
      tag,
      ~props={"className": classes} |. ReactDOMRe.objToDOMProps,
      children,
    );
  },
};

module Item = {
  let component = ReasonReact.statelessComponent("BreadCrumb.Item");
  let make =
      (
        ~active: bool=false,
        ~tag: string="li",
        ~className: option(string)=?,
        /* cssModule::(cssModule: option (Js.t {..}))=? */
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["breadcrumb-item", active ? "active" : "", unwrapStr(i, className)]
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes} |. ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
};
