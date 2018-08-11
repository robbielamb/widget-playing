let component = ReasonReact.statelessComponent("Table");

let make =
    (
      ~tag: string="table",
      ~bordered: bool=false,
      ~striped: bool=false,
      ~inverse: bool=false,
      ~hover: bool=false,
      ~reflow: bool=false,
      ~small: bool=false,
      ~responsive: bool=false,
      ~responsiveTag: string="div",
      ~classname: option(string)=?,
      children,
    ) => {
  ...component,
  render: _self => {
    let classes =
      [
        "table",
        bordered ? "table-bordered" : "",
        striped ? "table-striped" : "",
        inverse ? "table-inverse" : "",
        hover ? "table-hover" : "",
        reflow ? "table-reflow" : "",
        small ? "table-small" : "",
        Utils.unwrapStr(Utils.i, classname),
      ]
      |> String.concat(" ");
    let table =
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={"className": classes}  |. ReactDOMRe.objToDOMProps,
        children,
      );
    responsive ?
      ReactDOMRe.createElement(
        responsiveTag,
        ~props={"className": "table-responsive"} |. ReactDOMRe.objToDOMProps,
        [|table|],
      ) :
      table;
  },
};
